// task8sem3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <iterator>

using namespace std;
typedef  pair<int, int> monomial;  // степень, коэффициент
typedef list <monomial> polynomial;
typedef vector < polynomial> mnogochleny;

void show(polynomial p) {
    polynomial::iterator ip = p.begin();
    if (ip->second == 0 && ip->first != 0) ip++;
    cout << ip->second;
    if (ip->first > 0) cout << " * x^" << ip->first; 
    ip++;
    for (; ip != p.end(); ip++) {
        if (ip->second == 0) continue;
        else
        {
            if (ip->second < 0) cout << " - ";
            else cout << " + ";
            cout << abs(ip->second);
            if (ip->first > 0) cout << " * x^" << ip->first; 
        }
    }
    cout << "\n\n";
}

monomial operator * ( monomial &p, int k) {
    p.second *= k;
    return p;
}

monomial operator *= (monomial &p, int k ) {
    return p*k;
}

polynomial operator * ( polynomial &p, int k) {
    for (polynomial::iterator ip = p.begin(); ip != p.end(); ip++) {
        *ip *= k; //??????
      //  *ip =  (*ip) * k;
    }
    return p;
}

polynomial operator *= ( polynomial &p, int k) {
    return p*k;
}

monomial operator * (monomial p, monomial k) {
    monomial t;
    t.first = p.first + k.first;
    t.second = p.second * k.second;
    return t;
}

monomial operator *= (monomial p, monomial k) {
    monomial t = p * k;
    return t;
}

polynomial operator * (polynomial p,  monomial k) {
    polynomial t;
    monomial it;
     for (polynomial::iterator ip = p.begin(); ip != p.end(); ip++) {
        it = *ip * k;
        t.push_back(it);
     }   
 //    cout << "operator * ="; show(t); cout << "\n";
     return t;
}

polynomial operator *= (polynomial p, monomial k) {
    polynomial t;
    t = p * k;
    return t;
}

polynomial operator + (polynomial p, polynomial k) {
   
    for (polynomial::iterator ik = k.begin(); ik != k.end(); ik++ ) {
        polynomial::iterator ip = p.begin();
        while (ip != p.end()) {
            if (ip->first == ik->first) {
                ip->second += ik->second;
                break;
            }
         ip++; 
        }
        if (ip == p.end() && ik !=k.end()) 
            p.push_back(*ik);
    }
    p.sort();
    p.reverse();
    return p;
}

polynomial operator += (polynomial p, polynomial k) {
    return p + k;
}

polynomial operator - (polynomial p, polynomial k) {
 //   cout << "p begin -\n"; show(p);
 //   cout << "k begin -\n"; show(k);
    for (polynomial::iterator ik = k.begin(); ik != k.end(); ik++) {
        polynomial::iterator ip = p.begin();
        while (ip != p.end()) {
            if (ip->first == ik->first) {
                ip->second -= ik->second;
                break;
            }
            ip++;
        }
        if (ip == p.end() && ik != k.end())
            p.push_back((*ik)*(-1));
 //       cout << "p in -\n"; show(p); 
    }
    p.sort();
    p.reverse();
    return p;
}

polynomial operator -= (polynomial p, polynomial k) {
    return p - k;
}

int main()
{
    const int n = 5;
    mnogochleny a(n);
    int step2 = 2;
    a[0].push_back(make_pair(0, 1));  //1*x^0
    a[1].push_back(make_pair(1, 1));  //1*x^1
    show(a[0]); cout << "\n\n";
    show(a[1]); cout << "\n\n";
    for (int i = 1; i < n - 1; i++) {
        monomial t = make_pair(1, 2 * i + 1);     //2*x^1
        polynomial b = a[i] * t;
        polynomial c = a[i - 1] * i;
        step2 = i + 1;
        cout << "\n\n b \n";   show(b);
        cout << "\n\n c \n";   show(c); cout << "\n\n";
        a[i + 1] = b - c;             //2*x^2 - 1*x^0
        cout << "( ";
        show(a[i + 1]);
        cout << ") / " << step2 << "\n\n";
    }

    cout << "\n";
    
}
/* код для Падована
const int n = 11;
    mnogochleny a(n);
    monomial t = make_pair(1, 1);      
    a[0].push_back(make_pair(0, 1));   
    a[1].push_back(make_pair(0, 0));   
    a[2].push_back(make_pair(1, 1));   
    show(a[0]);
    show(a[1]);
    show(a[2]);
    for (int i = 3; i < n; i++) {
        polynomial b = a[i - 2] * t;
        a[i] = b + a[i - 3];             
        show(a[i]);
    }

    cout << "\n";
*/
/* код для чебышева 1 рода
const int n = 11;
    mnogochleny a(n);
    monomial t = make_pair(1, 2);     //2*x^1
    a[0].push_back(make_pair(0, 1));  //1*x^0
    a[1].push_back(make_pair(1, 1));  //1*x^1
    show(a[0]);
    show(a[1]);
    for (int i = 2; i < n; i++) {
        polynomial b = a[i - 1] * t;
        //   show(b);
        a[i] = b - a[i - 2];             //2*x^2 - 1*x^0
        show(a[i]);
    }

    cout << "\n";
*/
/* не работает для лежандра

*/