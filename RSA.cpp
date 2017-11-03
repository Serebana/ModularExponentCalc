//
// Created by Sergey on 02.03.2016.
//
#include "RSA.h"
using namespace std;
RSA::RSA() {
    for (int i = 0; i < N*2; ++i) {
        A[i]=0;
    }
    n=0;
    f= true;
}
// метод вводу обєкта
RSA RSA::Input(int a) {
    for (int i = 0; i <N ; ++i) {
        A[i]=rand()*rand();
    }
    n=N;
    return RSA();
}
// метод виводу обєкта,змінна а - назва обєкта
void RSA::Output(char a) {
    cout<<"\n N="<<dec<<n<<"||"<<a<<"=";
    for (int i = n; i >0 ; i--) {
        cout<<"(i="<<dec<<n-i<<")"<<hex<<A[i-1]<<"||";
    }
    if(n==0) cout<<0;
    cout<<"\n";
    return;
}
// операція додавання обєктів
RSA RSA::operator+(RSA &rsa) {
    RSA buf=*this;int k;
    if(n<rsa.n)
        buf.n=rsa.n;
    for (int i = 0; i < buf.n ; ++i) {
        if((0xffffffff-buf.A[i])<rsa.A[i])
        {
            if((rsa.f)||((!rsa.f)&&(buf.n<rsa.n)))
            {
                k = 1;
                while (buf.A[i + k] == 0xffffffff) {
                    buf.A[i + k] = 0;
                    k++;
                }
                if ((i + k) < buf.n)
                    buf.A[i + k]++;
            }
        }
        buf.A[i]+=rsa.A[i];
    }
    if(buf.A[buf.n]==1)
        buf.n++;
    return buf;
}
// метод інверсії обєкту
RSA RSA::Invert() {
    RSA buf,b=*this;buf.n=1;buf.A[0]=1;
    for (int i = 0; i <n ; ++i) {
        b.A[i]=~b.A[i];
    }
    b=b+buf;
    return b;
}
// операція віднімання обєктів
RSA RSA::operator-(RSA &rsa) {
    RSA b=*this;
    if(b<rsa)
    {
        cout<<"ERROR VARIABLE subtraction! ";
        return RSA();
    }
    RSA buf=rsa;
    buf=buf.Invert();
    buf.f=false;
    buf=b+buf;
    buf.f= true;
    if(buf>*this)
        buf.n--;
    while(buf.A[buf.n-1]==0)
        buf.n--;
    for (int i = buf.n; i <N*2; ++i) {
        buf.A[i]=0;
    }
    return buf;
}
// операція добутку обєктів
RSA RSA::operator*(RSA &rsa) {
    RSA buf;unsigned long long a;int k;
    buf.n=n+rsa.n;
    for (int i = 0; i <n ; ++i) {
        for (int j = 0; j <rsa.n ; ++j) {
            a=1;
            a*=A[i];
            a*=rsa.A[j];
            if((0xffffffff-buf.A[i+j])<(a&0xffffffff))
            {
                k=1;
                while(buf.A[i+j+k]==0xffffffff)
                {
                    buf.A[i+j+k]=0;
                    k++;
                }
                buf.A[i+j+k]++;
            }
            buf.A[i+j]+=a&0xffffffff;
            if((0xffffffff-buf.A[i+j+1])<(a>>32))
            {
                k=2;
                while(buf.A[i+j+k]==0xffffffff)
                {
                    buf.A[i+j+k]=0;
                    k++;
                }
                buf.A[i+j+k]++;
            }
            buf.A[i+j+1]+=a>>32;
        }
    }
    while((buf.A[buf.n-1]==0)&&(buf.n>0))
        buf.n--;
    return buf;
}
int RSA::operator==(RSA &rsa) {
    if(n!=rsa.n)
        return 0;
    for (int i = 0; i <n ; ++i) {
        if(A[i]!=rsa.A[i])
            return 0;
    }
    return 1;
}

int RSA::operator<(RSA &rsa) {
    if(n>rsa.n)
        return 0;
    if(n<rsa.n)
        return 1;
    for (int i = n-1; i >=0 ; i--) {
        if(A[i]>rsa.A[i])
            return 0;
        if(A[i]<rsa.A[i])
            return 1;
    }
    return 0;
}

int RSA::operator>(RSA &rsa) {
    if(n<rsa.n)
        return 0;
    if(n>rsa.n)
        return 1;
    for (int i = n-1; i >=0 ; i--) {
        if(A[i]<rsa.A[i])
            return 0;
        if(A[i]>rsa.A[i])
            return 1;
    }
    return 0;
}
// операція модуляції обєктів
RSA RSA::Sl(int l) {
    for (int j = 0; j < l; ++j) {
        for (int i = n - 1; i >= 0; i--) {
            if (A[i] >> 31) {
                if (i == (n - 1))
                    n++;
                A[i + 1]++;
            }
            A[i] <<= 1;
        }
    }
    return RSA();
}
//
RSA* Tab(RSA rsa,RSA* b) {
    RSA t=rsa;
    *b=rsa;
    for (int i = 1; i<N*32+1 ;i++) {
        t.Sl();
        *(b+i)=t;
    }
    return b;
}
// метод побудови таблиці зсунутого модуля, для редукції
RSA RSA::operator%(RSA &rsa) {
    RSA buf;
    static int i=0;
    static RSA B[N*32+1];
    static RSA *b =&B[0];
    if(i==0) {
        b = Tab(rsa, b);
        i=1;
    }
    buf=*this;
    int k=N*32;
    while(k>=0)
    {
        if((B[k]<buf)||(B[k]==buf))
            buf=buf-B[k];
        if(buf<B[k])
            k--;
    }
    while((buf.A[buf.n-1]==0)&&(buf.n>0))
        buf.n--;
    return buf;
}
// метод модулярного експоненціювання
RSA RSA::PowMod(RSA rsa, RSA rsa1) {
    RSA buf,buf1;buf.A[0]=1;buf.n=1;buf1=*this;unsigned int k;int n;
    for (int i = 0; i <rsa.n ; ++i) {
        k=rsa.A[i];n=31;
        while(n>=0)
        {
            buf=buf*buf;
            buf=buf%rsa1;
            if((k>>n)&1)
            {
                buf=buf*buf1;
                buf=buf%rsa1;
            }
            n--;
        }
    }
    while((buf.A[buf.n-1]==0)&&(buf.n>0))
        buf.n--;
    return buf;
}
