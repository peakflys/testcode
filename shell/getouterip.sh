#!/bin/sh 
#ip138=`curl http://www.ip138.com/ip2city.asp 2>/dev/null |grep '\[*\]' |cut -d "[" -f2 |cut -d "]" -f1` 
#ip138 = 'curl http://www.ip138.com/ip2city.asp 2>/dev/null |grep '\[*\]' |cut -d "[" -f2 |cut -d "]" -f1' 
#echo "$ip138 www.ip138.com" 
#f5ha=`curl http://www.f5ha.com/ip.php 2>/dev/null|cut -f1` 
#echo "$f5ha www.f5ha.com"
curl http://members.3322.org/dyndns/getip
