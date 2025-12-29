#include <iostream>
using namespace std;

typedef string infotype;

const int  N_STACK  = 2025;

struct stack{
    infotype info [N_STACK];
    int top;
};

void create_stack (stack &s) {
    s.top =-1;
}



bool is_full(stack s){
    return s.top == N_STACK-1;
}
bool empty(stack r){
    return r.top == -1;
}


void push (stack &s, infotype x){
    if (!is_full(s)){
        s.top++;
        s.info[s.top]=x;
    }else {
        cout << "its full";
    }
}

void pop(stack &s){
    if (!empty(s)){
        s.top --;
    }else{
        cout << "empty";
    }
}

void manageAction(stack &s_aksi, stack &s_redo, infotype aksi){
    if (aksi == "undo"|| aksi == "UNDO"){
        push (s_redo,s_aksi.info[s_aksi.top]);
        pop (s_aksi); 
    }else if (aksi == "redo"|| aksi == "REDO"){
        push (s_aksi,s_redo.info[s_redo.top]);
        pop (s_redo);
    }else{
        push (s_aksi,aksi);
    }
}

int totalDamage(stack s){
    int dmg = 0;
     while (!empty(s)) {
        if (s.info[s.top] == "ATTACK") {
            dmg += 30;
        } else if (s.info[s.top] == "DEFENSE") {
            dmg -= 5;
        }
        pop (s);
     }
    return dmg;
}

int main() {
    stack action, redo;
    infotype act;
    int x;

    create_stack (action);
    create_stack (redo);

    while (true){
        cout << "1. action?\n";
        cout << "2. total dmg output\n";
        cout << "3. exit\n";
        cin >> x;
        switch (x){
        case 1:
            cout << "enter action: ";
            cin >>act;
            manageAction(action,redo,act);
            break;
        case 2:
            cout << "total dmg" << totalDamage(action)<<endl;
            break;
        case 3:
           cout << "ok";
            return 0;
        default:
            break;;
        }


    }

    return 0;
}