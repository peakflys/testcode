#!/bin/bash
#使用方式:脚本后面提供一个搜索引擎关键词，用来搜索可以查IP的网站，比如 “IP”、“IP查询” 等关键词
#
#判断参数是否为空，为空则提示加参数，然后退出脚本
[ -z $1 ] && echo "you must give a keyword" && exit 4
clear
#此变量存储当前检测第几个网页
STEP=1
#此变量存储搜索关键词，是脚本传递进来的值
KEYWORD=$1
#如果当前目录存在info.txt则删除这个文件
[ -e info.txt ] && rm -rf info.txt
echo "获取本机公网地址中。。。。"
#此循环用来获取公网地址，如果获取不到则显示获取失败，并再次进行获取，如何获取到则退出循环。
while true;do
#用curl访问http://ip.chinaz.com页面，提取出公网IP地址。
MYIPADDR=`curl "http://ip.chinaz.com/" 2>/dev/null | grep "您的IP:" | awk -F 'strong|>|<' '{print $6}'`
if [ -z $MYIPADDR ];then
    echo "获取公网地址失败"
else
    echo "本机公网地址:$MYIPADDR"
    break
fi
done
#先定义此变量，用来存储当前搜索页面的最后一个页码
FINPAGE=1
#此变量存储搜索页码
PN=1
#当前搜索页小于等于当前搜索页的最后一个页码时，则进入循环。
while [ $PN -le $FINPAGE ];do
    #显示当前第几个搜索页。
    echo -e "\033[34;1m当前第$PN搜索页\033[0m\n"
       
    #用的是360的搜索引擎，因为百度的源码是压缩过的，提取字符比较困难。www.so.com/s?q=$KEYWORD&pn=$PN 这个url中，q=后面是搜索词，pn=后面是搜索结果的页码。分析一下360的搜索页就能看出。
       
    #用grep和awk提取出当前页面的最后一个页码。
    FINPAGE=`curl "www.so.com/s?q=$KEYWORD&pn=$PN&j=0" 2>/dev/null | grep '<strong>' | awk -F '<strong>|</strong>' '{print $2}'`
    echo "遍历当前搜索页可能页面的地址。。。"
       
    #提取出当前搜索页结果的所有网页地址。保存在WEBLIST变量中。
    WEBLIST=`curl "http://www.so.com/s?q=$KEYWORD&pn=$PN&j=0" 2>/dev/null | grep "</h3>"  | awk -F 'href=' '{print $2}' | cut -d '"' -f2`
    echo -e "遍历完成。。。开始筛选符合条件的网页。。。\n"
       
    #遍历当前搜索页的每个网页，分析网页中的内容。
    for i in `echo $WEBLIST`; do
        #打印相关信息。
        echo -e "当前检测第\033[33;1m$STEP\033[0m个网页,当前搜索页一共有`echo -e $WEBLIST | awk '{print NF}'`个网页"
           
        #用curl抓取当前网页的内容，匹配一下自己的公网地址。
        curl -m 5 $i 2>/dev/null | grep $MYIPADDR > /dev/null
           
        #如果匹配到，说明此网站可以查询IP地址信息。
        if [ $? -eq 0 ];then
            echo -e "\033[32;1m$i 符合，此网站可以查询IP信息\033[0m"
               
            #提取当前网页的域名，保存在DONAME变量中。
            DONAME=`echo "$i" |sed 's#^http://\(.*\)/*$#\1#g' |cut -d/ -f1`
               
            #用ping命令去解析此域名本地dns解析出来的IP地址，也就是这个可以查询IP地址信息网站的IP地址，保存在WEBIPADDR变量中
            WEBIPADDR=`ping -c 1 -w 1 $DONAME |cut -d/ -f1 | head -1 | awk -F '(' '{print $2}' |cut -d')' -f1`
               
            #用curl在http://ip.chinaz.com上解析出此网站IP的物理地址。保存在PHYADD变量中。
            PHYADD=`curl "http://ip.chinaz.com/?IP=$WEBIPADDR" 2>/dev/null | grep -A 1 '<span id="status" class="info1">' | tail -1 | awk -F '==>>' '{print $NF}' | cut -d '<' -f1`
            #将相关信息保存在info.txt中
            echo -e "$DONAME\t\t\t--\t\t\t$WEBIPADDR\t\t--\t\t$PHYADD" >> info.txt
               
        else
        echo -e "\033[31;1m$i 此网站pass\033[0m"
        fi
        let STEP+=1
    done
    let PN+=1
    let FINPAGE+=1
done
#将最后的结果进行去重，保存在result中。
cat info.txt | sort | uniq > result.txt
#显示出结果。
echo -e "\n\n结果显示：--------------------"
cat result.txt
