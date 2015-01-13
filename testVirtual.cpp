#include <iostream>

class Base
{
    public:
        Base()
        {
            //first construct Base, so Derive is ok
            clear();
        }
        virtual ~Base() {}
        virtual void clear()
        {
            memset(this,0,sizeof(*this));
        }
        virtual void print()
        {
            printf("%s: %d\n",__PRETTY_FUNCTION__, a);
        }
    private:
        int a;
};

class Derived : public Base
{
    public:
        Derived(int a, int b):a(a), b(b){}
        virtual ~Derived(){}
        virtual void print()
        {
            printf("%s: %d,%d\n",__PRETTY_FUNCTION__, a, b);
        }
    private:
        int a;
        int b;
};

class Base1
{
	public:
	/*	void print()
		{cout<<"This is print()"<<endl;}*/
		virtual void vprint1()
		{cout<<"This is vprint1()"<<endl;}
		virtual void vprint2()
		{cout<<"This is vprint2()"<<endl;}
};

int main()
{
    Base b;
    Derived d(5,6);
    Base* pb = &b;
    Base* pd = &d;
    Derived* pdd = &d;

    b.print();
    printf("1 ok\n");
    d.print();
    printf("2 ok\n");
    /*
    pb->print();   //virtual func call crash
    printf("3 ok\n");
    */
    pd->print();
    printf("4 ok\n");
    pdd->print();
    printf("5 ok\n");
    /*
	typedef void(*pFun)(void) ;
	pFun pf = NULL;
	int *vt = NULL;
	Base1 b;
	int size =  sizeof(&Base1::vprint1);
	cout<<"Base1 VirtualTable addr : "<<(int *)&b<<endl;
	vt = (int *)*(int *)&b;
	cout<<"Base1 First VirtualFunc addr: "<<vt[0]<<endl;
	//pf = (void *)*(int *)&b;//error
	pf = (pFun)vt[0];
	pf();
	cout<<"Base1 Second VirtualFunc addr: "<<vt[1]<<endl;
	pf = (pFun)(vt[4]);
	pf();
       */
}
