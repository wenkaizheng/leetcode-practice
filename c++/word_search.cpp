#include <vector> // for 2D vector
#include <iostream>
#include <array>
#include <string>
using namespace std;
struct TrieNode {
    string word { "" };
    array<TrieNode*, 26> chars { nullptr };
};
using pairs = std::pair<int, int>;
class Solution1 {
public:
    bool exist(vector<vector<char>>& board, string word) {
         for(int i = 0; i<board.size();i++){
            for(int j = 0; j< board[i].size();j++){
                if(board[i][j] == word.front()){
                   if(dfs(word,1,board,{i,j})){
                       return true;
                   }
                }
            }
         }
         return false;
    }
private:
    bool dfs(string word,int index,vector<vector<char>>& board,pairs p ){
        if (index == word.size()) 
        {
            return true;
        }
        auto [i,j] = p;
        char cur = board[i][j];
        char next = word[index];
        board[i][j] = '\0';
        auto IsValid = [&](int i, int j) {
            return (i >= 0 && i < board.size()) &&
                   (j >= 0 && j < board[i].size()) &&
                   (board[i][j] == next);
        };
        if( (IsValid(i+1,j) && dfs(word,index+1,board,{i+1,j})) ||
           (IsValid(i-1,j) && dfs(word,index+1,board,{i-1,j})) ||
          (IsValid(i,j+1) && dfs(word,index+1,board,{i,j+1})) ||
           (IsValid(i,j-1) && dfs(word,index+1,board,{i,j-1}))){
            return true;
        }
        board[i][j] = cur;
        return false;
    }
};
class Solution2 {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> result;
        TrieNode* root = new TrieNode();
        for (const auto& word : words) {
            auto it = root;
            for (auto c : word) {
                int idx = c - 'a';
                if (it->chars[idx] == nullptr) {
                    it->chars[idx] = new TrieNode();
                }
                it = it->chars[idx];
            }
            it->word = word;
        }

        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[i].size(); ++j) {
                int idx = board[i][j] - 'a'; 
                if (root->chars[idx] != nullptr) {
                    search(board, result, i, j, root);
                }
            }
        }

        return result;
    }
private:
    void search(vector<vector<char>>& board_ptr, vector<string>& result_ptr, int i, int j, TrieNode* node) {

        int idx = board_ptr[i][j] - 'a'; 
        node = node->chars[idx];
        if (node) {
            if (!(node->word).empty()) {
                result_ptr.emplace_back(node->word);
                node->word = "";
            }

            auto IsValidDir = [&board_ptr](int i, int j) -> bool {
                return i >= 0 && i < board_ptr.size()
                    && j >= 0 && j < board_ptr[i].size()
                    && board_ptr[i][j] != '\0';
            };

            char letter = board_ptr[i][j];
            board_ptr[i][j] = '\0';
			
            if (IsValidDir(i - 1, j)) search(board_ptr, result_ptr, i - 1, j, node);
            if (IsValidDir(i + 1, j)) search(board_ptr, result_ptr, i + 1, j, node);
            if (IsValidDir(i, j - 1)) search(board_ptr, result_ptr, i, j - 1, node);
            if (IsValidDir(i, j + 1)) search(board_ptr, result_ptr, i, j + 1, node);

            board_ptr[i][j] = letter; // unmark visited
        }
    }
};
int main(){
    Solution2 s2 = Solution2();
    string a[4]= {"oath","pea","eat","rain"};
    vector<string> b;
    b.insert(b.begin(),a,a+4);
    vector<vector<char>> vect2 {
          {'o','a','a','n'},
          {'e','t','a','e'},
          {'i','h','k','r'},
          {'i','f','l','v'}
    };
   vector<string> v2 =  s2.findWords(vect2,b);
   for (int i =0 ;i<v2.size();i++){
       cout<< v2[i] << endl;
   }
   Solution1 s1 = Solution1();
   vector<vector<char>> vect1 {
          {'A','B','C','E'},
          {'S','F','C','S'},
          {'A','D','E','E'}
    };
    bool rc = s1.exist(vect1,"ABCCED");
    cout << rc << endl;
}