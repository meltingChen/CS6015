
class Expr {
public:
   };

class Num : public Expr {
public:
    int val;
    Num(int val) { this->val = val;}
    bool equals(Expr *e){
        
    }
};

class Add : public Expr {
public:
    Expr *lhs; Expr *rhs;
    Add(Expr *lhs, Expr *rhs){
        this->lhs = lhs; this->rhs = rhs;}
};

class Mult : public Expr {
public:
    Expr *lhs; Expr *rhs;
    Mult(Expr *lhs, Expr *rhs) {
        this->lhs = lhs;
        this->rhs = rhs;
    }
};
