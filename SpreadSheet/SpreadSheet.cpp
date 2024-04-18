#include "SpreadSheet.h"

SpreadSheet::SpreadSheet():rowcnt(2),colcnt(2){   
    board = new Cell*[rowcnt];
    for(std::size_t i = 0; i < rowcnt;i++){
        board[i] = new Cell[colcnt];
    }
}

SpreadSheet::SpreadSheet(const SpreadSheet &rhv):rowcnt(rhv.rowcnt),colcnt(rhv.colcnt){    
    board = new Cell*[rowcnt];
    for(std::size_t i = 0; i<rowcnt;i++){
        board[i] = new Cell[colcnt];
    }
    for(std::size_t i = 0;i<rowcnt;i++){
        for(std::size_t j = 0;j<colcnt;j++){
            board[i][j] = rhv.board[i][j];
        }
    }
}

SpreadSheet::SpreadSheet(SpreadSheet &&rhv):rowcnt(rhv.rowcnt),colcnt(rhv.colcnt),board(rhv.board){    
    rhv.board = nullptr;
    rhv.rowcnt = 0;
    rhv.colcnt = 0;
}

SpreadSheet::SpreadSheet(size_t size):rowcnt(size),colcnt(size){    
    board = new Cell*[rowcnt];
    for(std::size_t i = 0;i<rowcnt;i++){
        board[i] = new Cell[colcnt];
    }
}

SpreadSheet::SpreadSheet(size_t row, size_t col):rowcnt(row),colcnt(col){    
    board = new Cell*[rowcnt];
    for(std::size_t i = 0;i<rowcnt;i++){
        board[i] = new Cell[colcnt];
    }
}

SpreadSheet::~SpreadSheet(){    
    for(int i = 0; i<rowcnt;i++){
        delete [] board[i];
    }
    delete [] board;
}

const SpreadSheet &SpreadSheet::operator=(const SpreadSheet &rhv){    
    if (this != &rhv){
        if (rowcnt != rhv.rowcnt || colcnt != rhv.colcnt){
            for(int i = 0;i<rowcnt;i++){
                delete [] board[i];
            }
            delete [] board;
            rowcnt = rhv.rowcnt;
            colcnt = rhv.colcnt;
            board = new Cell*[rowcnt];
            for(int i = 0; i<rowcnt;i++){
                board[i] = new Cell[colcnt];
            }
        }
        for(int i = 0;i<rowcnt;i++){
            for(int j = 0; j<colcnt;j++){
                board[i][j] = rhv.board[i][j];
            }
        }

    }
    return *this;
}

const SpreadSheet &SpreadSheet::operator=(SpreadSheet &&rhv){    
    for(int i = 0;i<rowcnt;i++){
        delete [] board[i];
    }
    delete [] board;
    rowcnt = rhv.rowcnt;
    colcnt = rhv.colcnt;
    board = rhv.board;

    rhv.board = nullptr;
    rhv.rowcnt = 0;
    rhv.colcnt = 0;

    return *this;
}
       
SpreadSheet::Column::Column(Cell *col){    
    this->col = col;
}

Cell &SpreadSheet::Column::operator[](size_t pos){    
    return col[pos];
}

const Cell &SpreadSheet::Column::operator[](size_t pos) const{    
    return col[pos];
}

SpreadSheet::Column SpreadSheet::operator[](size_t pos){    
    if(pos >= rowcnt){
        throw std::out_of_range("Out_of_range");
    }
    return Column(board[pos]);
}
const SpreadSheet::Column SpreadSheet::operator[](size_t pos) const{    
   if(pos >= rowcnt){
        throw std::out_of_range("Out_of_range");
    }
    return Column(board[pos]); 
}

void SpreadSheet::clear() noexcept{    
    if (board){
        for (size_t i = 0; i < rowcnt; i++) {
            delete[] board[i];
        }
        delete[] board;
        board = nullptr;
        rowcnt = 0;
        colcnt = 0;
    }
}

size_t SpreadSheet::row() const{    
    return rowcnt;
}

size_t SpreadSheet::col() const{    
    return colcnt;
}

void SpreadSheet::mirrorH(){    
    if(rowcnt == 0){
        throw std::logic_error("No elements in SpreadSheet");
    }
    if (rowcnt == 1){return;}
    for(int i = 0; i<rowcnt/2;i++){
        for(int j = 0; j<colcnt;j++){
            std::swap(board[i][j],board[rowcnt-i-1][j]);
        }
    }
}

void SpreadSheet::mirrorV(){    
    if(rowcnt == 0){
        throw std::out_of_range("No elements in SpreadSheet");
    }
    if (colcnt == 1){return;}
    for(int i = 0;i<rowcnt;i++){
        for(int j = 0;j<colcnt/2;j++){
            std::swap(board[i][j],board[i][colcnt-j-1]);
        }
    }
}

void SpreadSheet::mirrorD(){    
    if(rowcnt == 0){
        throw std::out_of_range("No elements in SpreadSheet");
    }
    if (rowcnt == 1 || colcnt == 1){return;}
    if (rowcnt == colcnt){
        for(int i = 0; i<rowcnt;i++){
            for(int j = i+1; j<colcnt;j++){
                std::swap(board[i][j],board[j][i]);
            }
        }
    }else{
        Cell** newBoard = new Cell*[colcnt];
        for(int i = 0; i<colcnt;i++){
            newBoard[i] = new Cell[rowcnt];
        }
        for(int i = 0; i<rowcnt;i++){
            for(int j = 0;j<colcnt;j++){
                newBoard[j][i] = board[i][j];
            }
        }
        
        for(int i = 0; i<rowcnt;i++){
            delete [] board[i];
        }
        delete [] board;
        board = newBoard;
        newBoard = nullptr;
        std::swap(rowcnt,colcnt);
    }
}

void SpreadSheet::mirrorSD(){   
    if(rowcnt == 0){
        throw std::out_of_range("No elements in SpreadSheet");
    }
    if (rowcnt == 1){return;}
    if (rowcnt == colcnt){
        for(int i = 0; i<rowcnt;i++){
            for(int j = 0; j<rowcnt-i;j++){
                std::swap(board[i][j],board[rowcnt-j-1][colcnt-i-1]);
            }
        }
    }else{
        Cell** newBoard = new Cell*[colcnt];
        for(int i = 0; i<colcnt;i++){
            newBoard[i] = new Cell[rowcnt];
        }
        for(int i = 0; i<colcnt;i++){
            for(int j = 0;j<rowcnt;j++){
                newBoard[i][j] = board[rowcnt-j-1][colcnt-i-1];
            }
        }
        
        for(int i = 0; i<rowcnt;i++){
            delete [] board[i];
        }
        delete [] board;
        board = newBoard;
        newBoard = nullptr;
        std::swap(rowcnt,colcnt);
    }
}

void SpreadSheet::rotate(int cnt){    
    if (cnt < 0){
        throw std::invalid_argument("Invalid_Argument:Count for rotates should be a positive number");
    }
    cnt%=4;
    for(int i = 0;i<cnt;i++){
        mirrorD();
        mirrorV();
    }    
}

void SpreadSheet::removeRow(size_t row){    

    if (row >= rowcnt){
        throw std::invalid_argument("Out of range");
    }
    if (rowcnt == 0){
        throw std::out_of_range("No elements in SpreadSheet");
    }else if(rowcnt == 1){
        clear();
        return;
    }
    std::size_t newRowCount = rowcnt - 1;
    Cell** newBoard = new Cell*[newRowCount];
    for(int i = 0; i<newRowCount;i++){
        newBoard[i] = new Cell[colcnt];
    }
    int newRow = 0;
    for(int i = 0; i<rowcnt;i++){
        if (i == row){continue;}
        for(int j = 0; j<colcnt;j++){
            newBoard[newRow][j] = board[i][j];            
        }
        newRow++;
    }
    
    for(int i = 0; i<rowcnt;i++){
        delete [] board[i];
    }
    delete [] board;
    board = newBoard;
    newBoard = nullptr;
    rowcnt = newRowCount;
}

void SpreadSheet::removeRows(std::initializer_list<size_t> rows){    
    std::vector<size_t> vec(rows);
    std::sort(vec.begin(), vec.end());
    std::reverse(vec.begin(),vec.end());
    auto iter = std::unique(vec.begin(),vec.end());
    vec.resize(distance(vec.begin(), iter));

    auto it = rows.begin(); 
    for(int i = 0;i<rows.size();i++){        
        removeRow(*(it++));
    }
}

void SpreadSheet::removeCol(size_t col){    
    if (col >= colcnt){
        throw std::invalid_argument("Out of range");
    }
    if (colcnt == 0){
        throw std::out_of_range("No elements in SpreadSheet");
    }
    std::size_t newColCount = colcnt - 1;
    Cell** newBoard = new Cell*[rowcnt];
    for(int i = 0; i<rowcnt;i++){
        newBoard[i] = new Cell[newColCount];
    }
    int newCol = 0;
    for(int i = 0; i<rowcnt;i++){
        newCol = 0;
        for(int j = 0; j<colcnt;j++){
            if (j == col){continue;}
            newBoard[i][newCol] = board[i][j];
            newCol++;
        }
    }

    for(int i = 0; i<rowcnt;i++){
        delete [] board[i];
    }
    delete [] board;
    board = newBoard;
    newBoard = nullptr;
    colcnt = newColCount;
}

void SpreadSheet::removeCols(std::initializer_list<size_t> cols){    
    std::vector<size_t> vec(cols);
    std::sort(vec.begin(), vec.end());
    std::reverse(vec.begin(),vec.end());
    auto iter = std::unique(vec.begin(),vec.end());
    vec.resize(distance(vec.begin(), iter));
    for(auto it = cols.begin();it!=cols.end();it++){
        removeCol(*it);
    }
}

void SpreadSheet::resizeRow(size_t r){     
    if (r == 0){clear();return;}
    if (r == rowcnt){return;}
    
    Cell** newBoard = new Cell*[r];
    for(int i = 0; i<r;i++){
        newBoard[i] = new Cell[colcnt];
    }

    size_t tmpRows = std::min(r,rowcnt);
    for(int i = 0; i < tmpRows; i++){
        for(int j = 0; j<colcnt;j++){
            newBoard[i][j] = board[i][j];
        }
    }
    for(int i = 0; i < rowcnt; i++){
        delete [] board[i];
    }
    delete [] board;
    board = newBoard;
    rowcnt = r;
}

void SpreadSheet::resizeCol(size_t c){    
    if (c == 0) {
        clear();
        return;
    }
    if (c == colcnt) {
        return;
    }

    Cell** newBoard = new Cell*[rowcnt];
    for (size_t i = 0; i < rowcnt; ++i) {
        newBoard[i] = new Cell[c];
    }

    size_t newCols = std::min(c,colcnt);
    for (size_t i = 0; i < rowcnt; ++i) {
        for (size_t j = 0; j < newCols; ++j) {
            newBoard[i][j] = board[i][j];
        }
    }

    for (size_t i = 0; i < rowcnt; ++i) {
        delete[] board[i];
    }
    delete[] board;

    board = newBoard;
    colcnt = c;
}

void SpreadSheet::resize(size_t r, size_t c){    
    resizeRow(r);
    resizeCol(c);
}

bool operator==(const SpreadSheet &lhv, const SpreadSheet &rhv){
    if (lhv.row() != rhv.row() || lhv.col() != rhv.col()){
        return false;
    }
    for(int i = 0; i<lhv.row();i++){
        for(int j = 0; j<lhv.col();j++){
            if (lhv[i][j] != rhv[i][j]){
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const SpreadSheet &lhv, const SpreadSheet &rhv){
    return !(lhv == rhv);
}

std::ostream &operator<<(std::ostream &out, const SpreadSheet &ob){
    int maxLen = ob.max_length();
    int width = maxLen;
    size_t row = ob.row();
    size_t col = ob.col();

    int totalRowWidth = col * (width + 3) + 1;
    out << std::string(totalRowWidth, '-') << "\n";

    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            if (j < ob.col()) {
                out << "| " << std::setw(width) << std::left << ob[i][j] << " ";
            } else {
                out << "| " << std::setw(width) << std::left << "_ " ;
            }
        }
        out << "|\n" << std::string(totalRowWidth, '-') << "\n";
    }

    return out;

    
}

SpreadSheet SpreadSheet::slice(std::initializer_list<size_t> rows, std::initializer_list<size_t> cols){
    std::vector<size_t> vecRows(rows);
    auto it = std::unique(vecRows.begin(),vecRows.end());
    vecRows.resize(distance(vecRows.begin(), it));

    std::vector<size_t> vecCols(cols);
    auto iter = std::unique(vecCols.begin(),vecCols.end());
    vecCols.resize(distance(vecCols.begin(), iter));

    size_t newRow = vecRows.size();
    size_t newCol = vecCols.size();

    SpreadSheet tmp(newRow,newCol);
    
    for(int i = 0; i<newRow;i++){
        for(int j = 0; j<newCol;j++){
            tmp[i][j] = board[vecRows[i]][vecCols[j]];
        }
    }

    return tmp;
    
}


int SpreadSheet::max_length() const
{ 
    int max = 0;
    for(size_t i = 0; i < rowcnt; ++i)
    {
        for(size_t j = 0; j < colcnt; ++j)
        {
            std::string str = board[i][j];
            max = max < str.length() ? str.length() : max;
        }
    }
    return max;
}

