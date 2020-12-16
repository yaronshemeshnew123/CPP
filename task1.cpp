#include <iostream>
#include <cmath>
using namespace std;

/**///teacher notes: many parts of the code used mixed indentation of spaces and tabs which ruined it looks. indentation was changed.

class Equation{
private:
    double a=0;
    double b=0;
    double c=0;
    double *solutions;
    size_t solutions_size;
    
    void solve()
    {
        double result;
	result=b*b-4*a*c;

	if(result<0)
	{
	    solutions_size=0;
	}
	else
        {
            if(result==0)
            {
                solutions_size=1;
            }
            else
            {
                solutions_size=2;
            }
            result=sqrt(result);
	    solutions=new double[2]; /**///[-] memory leak: should "delete[] solution" before assigning new.
	    solutions[0]=(-b+result)/(2*a);
	    solutions[1]=(-b-result)/(2*a);

        }

    }

public:
    
    /**//*
    * [?] unecessary call to solve() since set_* methods already do that.
    * 
    * [-] possible memory leak. If Equation throws in consturctor, the
    * destructor will not be called and the solutions array will leak.
    * several possible fixes: manual-check, rule-of-zero, try-function-block.
    *//**/
    Equation(double a,double b,double c)
    {
	set_a(a);
	set_b(b);
	set_c(c);
	solve(); 
    }
    
    /**///[?] would be better to use initializer list here
    Equation(const Equation& eq)
    {
        this->a=eq.get_a();
        this->b=eq.get_b();
        this->c=eq.get_c();
        solve();
    }
    ~Equation()
    {
        //remainder
	if(this->solutions!=nullptr) /**///no need to test for nullptr before deleting. you can saely call delete on a nullptr
	{
		delete [] solutions;
		solutions=nullptr;
	}
		
    }

    void set_a(double a)
    {
	if(a==0)
	{
		throw invalid_argument("a cant be zero");
	}
		
        this->a=a;
        solve();
    }

    double get_a() const
    {
     return this->a;
    }
    
    void set_b(double b)
    {
        this->b=b;
        solve();
    }
    
    double get_b() const
    {
	return this->b;
    }
    
    void set_c(double c)
    {
        this->c=c;
        solve();
    }
    
    double get_c() const
    {
	return this->c;
    }
     
    /**//*
    * no need to call solve() here if you call it whenever you set values.
    * but you forgot to call it in the operator methods below, which is why
    * you felt compelled to place it here. but this is the wrong approach.
    * you should fix the operator methods instead.
    */
    size_t get_solutions_size()
    {
	solve(); 
	return solutions_size;
    }

    double const * const get_solutions()
    {
	return solutions;
    }

    /**///forgot to call solve(); solutions will be set to old values.
    Equation& operator= (const Equation& o) {
	this->a = o.a;
	this->b = o.b;
	this->c = o.c;

	return *this;
    }

    /**///forgot to call solve();
    Equation& operator+ (int n){
	this->c+=n;
	return *this;
    }

    /**///forgot to call solve();
    Equation& operator+ (const Equation& o){
	this->a+=o.get_a();
	this->b+=o.get_b();
	this->c+=o.get_c();
	return *this;
    }

    friend Equation& operator+(int value,Equation& eq);
    friend ostream& operator <<(ostream& out, const Equation& eq);
};

ostream& operator <<(ostream& out, const Equation& eq) {
    out << eq.get_a() << "X^2+" << eq.get_b() << "X+"<<eq.get_c()<<"=0";
    return out;
}

/**///forgot to call solve()
Equation& operator+(int num,Equation& o)
{
    o.set_c(o.get_c()+num);
    return o;

}

int main()
{
    Equation eq(10,20,30);
    cout << eq << endl;
    //should print: 10X^2 + 20X + 30 = 0
    cout << eq.get_solutions_size() << endl;
    //should print 0
    cout << -20 + eq << endl;
    //should print: 10X^2 + 20X + 10 = 0
    cout << eq.get_solutions_size() << endl;
    //should print 1
    cout << eq.get_solutions()[0] << endl;
    //should print -1
    cout << Equation(1,5,3) + Equation(2,6,4) << endl;
    //should print: 3X^2 + 11X + 7 = 0
    eq = Equation(1,3,-4);
    cout << eq << endl;
    //should print 1X^2 + 3X + -4 = 0
    cout << eq.get_solutions_size() << endl;
    //should print 2
    cout << "X1 = " << eq.get_solutions()[0] << endl;
    //should print: X1 = 1
    cout << "X2 = " << eq.get_solutions()[1] << endl;
    //should print: X2 = -4
    
    /**///teacher test code from here:
    const Equation teacheq(1,2,3);
    const Equation teacheq2(teacheq);
    
    /**///^^^
    return 0;
}
