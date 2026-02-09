//TODO
//negative angles
//exact value to angle
#include <iostream>
#include <string>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <chrono>
#include <thread>


#ifdef LOCAL 
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

int six[] = {1, 5};
int three[] = {1, 2};
int four[] = {1, 3};

int diff;

std::string exact(int a, int b, const std::string& name) {
    int period = (name == "tan") ? b : 2 * b;
    a = ((a % period) + period) % period;
    
    //quadrant and angle
    int ref = a;
    int sign = 1;

    if (name == "sin" || name == "cos") {
        if (a <= b) {  
            if (a > b/2) {
                ref = b - a; 
                if (name == "sin") sign = 1;
                if (name == "cos") sign = -1;
            }
        } else {
            ref = a - b; 
            if (a <= 3*b/2) { 
                if (name == "sin") sign = -1;
                if (name == "cos") sign = -1;
            } else {
                if (name == "sin") sign = -1;
                if (name == "cos") sign = 1;
            }
        }
    } else {
        if (a > b/2) {
            ref = a - b/2;
            sign = -1;
        }
    }

    auto val = [&](int num, int den, const std::string& func) -> std::string {
        if (den % 6 == 0 && (num == 1 || num == 5)) {
            if (func == "sin") return "1/2";
            if (func == "cos") return "sqrt3/2";
            if (func == "tan") return "1/sqrt3";
        }
        if (den % 6 == 0 && (num == 2 || num == 4)) {
            if (func == "sin") return "sqrt3/2";
            if (func == "cos") return "1/2";
            if (func == "tan") return "sqrt3";
        }
        if (den % 4 == 0 && (num == 1 || num == 3)) {
            if (func == "sin" || func == "cos") return "sqrt2/2";
            if (func == "tan") return "1";
        }
        if (den % 3 == 0 && (num == 1 || num == 2)) {
            if (func == "sin") return "sqrt3/2";
            if (func == "cos") return "1/2";
            if (func == "tan") return "sqrt3";
        }
        if (num == den / 2) {
            if (func == "sin") return "1";
            if (func == "cos") return "0";
            if (func == "tan") return "undefined";
        }
        if (num == 0) {
            if (func == "sin") return "0";
            if (func == "cos") return "1";
            if (func == "tan") return "0";
        }
        return "nil";
    };

    std::string res = val(ref, b, name);
    if (res != "0" && res != "undefined") {
        if (sign == -1) res = "-" + res;
    }

    return res;
}
std::pair<std::string, std::string> pr(int id, std::string name) {
    std::string T;
    if (id == 1) {
        T = "/6";
    } else if (id == 2) {
        T = "/3";
    } else if (id == 3) {
        T = "/4";
    }

    std::string S = "";
    int xx = std::rand() % 2;
    int prid = std::rand() % diff + 1;
    std::string ans = "";
    if (id == 1) {
        int num = six[xx] + (prid * 6);
        S += std::to_string(num);
        S += T;
        ans = exact(num, 6, name);
    } else if (id == 2) {
        int num = three[xx] + (prid * 3);
        S += std::to_string(num);
        S += T;
        ans = exact(num, 3, name);
    } else if (id == 3) {
        int num = four[xx] + (prid * 4);
        S += std::to_string(num);
        S += T;
        ans = exact(num, 4, name);
    }
    return std::make_pair(S, ans);
}       

        

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    const char* fun[] = {"sin", "cos", "tan"};
    int no[] = {1, 2, 3};
    int sz2 = sizeof(no) / sizeof(no[0]);
    
    
    std::srand(std::time(nullptr));
    int sz = sizeof(fun) / sizeof(fun[0]);


    std::cout << "start" << '\n';
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "enter difficulty (1-20): \n";

    std::cin >> diff;

    while (diff != 0) {
        const char* randfun = fun[std::rand() % sz];
        int randid = no[std::rand() % sz2];
        std::pair<std::string, std::string> op = pr(randid, randfun);
        if (randfun == "sin") {
            std::cout << "sin((" << op.first << ")π" << ")" << '\n';
        } else if (randfun == "cos") {
            std::cout << "cos((" << op.first << ")π" << ")" << '\n';
        } else if (randfun == "tan") {
            std::cout << "tan((" << op.first << ")π" << ")" << '\n';
        }
        std::string ans;
        std::cin >> ans;
        if (ans == op.second) std::cout << "correct!" << '\n';
        else std::cout << "incorrect!" << '\n';
        if (ans == "0") diff = 0;
    }

    


    return 0;
}

