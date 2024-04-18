#include "Cell.h"

Cell::Cell():val("_"){}  

Cell::Cell(const Cell &rhv):val(rhv.val){}  

Cell::Cell(Cell &&rhv):val(std::move(rhv.val)){}   

Cell::Cell(int val){  
    this->val = std::to_string(val);
}

Cell::Cell(double val){  
    this->val = std::to_string(val);
}

Cell::Cell(char val){  
    this->val = val;
}

Cell::Cell(bool val){  
    this->val = val ? "true":"false";
}

Cell::Cell(std::string val):val(val){}  

Cell::Cell(const std::vector<int> &val){  
    for(auto it = val.begin();it!=val.end();it++){
        this->val += std::to_string(*it) + ",";
    }
    this->val.pop_back();
}

const Cell &Cell::operator=(const Cell &rhv){  
    if (this != &rhv){
        val = rhv.val;
    }
    return *this;
}

const Cell &Cell::operator=(Cell &&rhv){  
   val = std::move(rhv.val);
   return *this; 
}

const Cell &Cell::operator=(int rhv){  
    val = std::to_string(rhv);
    return *this;
}

const Cell &Cell::operator=(double rhv){  
    val = std::to_string(rhv);
    return *this;
}

const Cell &Cell::operator=(char rhv){  
    val = rhv;
    return *this;
}

const Cell &Cell::operator=(bool rhv){  
    val = rhv ? "true":"false";
    return *this;
}

const Cell &Cell::operator=(std::string rhv){  
    val = rhv;
    return *this;
}

const Cell &Cell::operator=(const std::vector<int> &rhv){  
    val = "";
    for(auto it = rhv.begin();it!=rhv.end();it++){
        val+=std::to_string(*it)+",";
    }
    this->val.pop_back();
    return *this;
}

Cell::operator int(){  
   try{
        return std::stoi(val);
   }catch(const std::invalid_argument& e){
        throw std::invalid_argument("Cannot convert string to integer");
   }
}

Cell::operator double(){  
    try{
        return std::stod(val);
    }catch (const std::invalid_argument& e){
        throw std::invalid_argument("Cannot convert stringn to double");
    }
}

Cell::operator char(){   
    return val[0];
}

Cell::operator bool(){  
    if (val == "true"){
        return true;
    }else if (val == "false"){
        return false;
    }else{
        throw std::invalid_argument("Cannot convert string to boolean");
    } 
}

Cell::operator std::string(){  
    return val;
}

Cell::operator std::vector<int>(){  
    if (val == ""){
        throw std::logic_error("Cell is empty");
    }
    std::vector<int> tmp;
    std::string forTemp = "";
    for(int i = 0; i<val.size();i++){
        if (std::isdigit(val[i])){
            forTemp += val[i];
        }else if(val[i] == ','){
            if (i == 0){
                throw std::invalid_argument("cant convert to vector");
            }
            tmp.push_back(std::stoi(forTemp));
            forTemp = "";
        }else{
            throw std::invalid_argument("cant convert to vector");
        }
    }
    if (forTemp.size() != 0){
        tmp.push_back(std::stoi(forTemp));
    }
    return tmp;
}

bool operator==(const Cell &lhv, const Cell &rhv){  
    return lhv.val == rhv.val;
}

bool operator!=(const Cell& lhv, const Cell& rhv){  
    return !(lhv == rhv);
}

std::ostream &operator<<(std::ostream &out, const std::vector<int> &ob){  
    out<<"[";
     for (size_t i = 0; i < ob.size(); ++i) {
        out << ob[i]; 
        if (i != ob.size() - 1) {
            out << ", ";
        }
    } 
    out<<"]";
    return out;
}

std::ostream &operator<<(std::ostream &out, const Cell &ob){  
    out << ob.val;
    return out;
}

std::istream &operator>>(std::istream &in,Cell &ob){  
    in>>ob.val;
    return in;
}

