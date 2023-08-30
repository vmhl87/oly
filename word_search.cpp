#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
    Essentially, I used a modified floodfill algorithm:
     - loop thru the 2d array of characters and store the positions of
       characters that match the start of the target word
     - from each of these start positions, we can initialize a "word"
       which is defined by its end position (which right now is its start)
       and its direction, and whether or not it has bent
     - loop thru the chars of the target word:
        - for each character we advance each "word" by searching for this
          target character in a position either in front or 90 degrees to
          the end of the word (if the word has already bent, ignore
          characters at 90 degrees to the current direction)
        - initialize a new word for each new character we find, and delete
          the old word
     - output the number of words
*/

// datastructure to store words more easily
struct coord{
    // row + column of the current end of the word
    int r;
    int c;
    // direction
    int dir=-1;
    // is this word able to bend (i.e. has it not already bent)
    bool turn=true;
};

int main(){
    // due to a number of reasons it is more efficient to represent
    // words' directions as ints rather than x,y offsets, so we make
    // a table from dir -> x,y offset
    int dirmap[16] = {
        1,0,   //0
        1,1,   //1
        0,1,   //2
        -1,1,  //3
        -1,0,  //4
        -1,-1, //5
        0,-1,  //6
        1,-1   //7
    };
    // input target word and rows/columns
    string word;
    cin >> word;
    int len=word.length(),r,c;
    cin >> r >> c;
    // initialize vector (basically dynamic size array) of words
    vector<struct coord> words;
    // initialze 2d array of chars and input them
    char letters[r][c],tmp;
    for(int i=0;i<r;i++)for(int j=0;j<c;j++){
        cin >> tmp;
        letters[i][j] = tmp;
        // if this character matches the start of the target word,
        // initialize a new word
        if(tmp==word[0]){
            struct coord temp;
            temp.r=i;temp.c=j;
            words.push_back(temp);
        }
    }
    // create a temporary vector of words
    vector<struct coord> t_words;
    // loop through all words
    for(coord i: words){
        // loop through all characters around this character
        for(int rr=max(0,i.r-1);rr<min(r,i.r+2);rr++)
        for(int cc=max(0,i.c-1);cc<min(c,i.c+2);cc++){
            // check if this character is a) the next character in target
            // word and b) not the original character
            if(rr!=i.r&&cc!=i.c&&letters[rr][cc]==word[1]){
                // create a new coord to specify the position of a word
                // ending at this new character, and pointing in whatever
                // direction it is relative to the original one
                struct coord temp;
                temp.r=rr;temp.c=cc;
                if(rr>i.r)temp.dir=2-cc+i.c;
                else if(rr<i.r)temp.dir=6+cc-i.c;
                else temp.dir=2-(cc-i.c)*2;
                // push this word to the temporary vector
                t_words.push_back(temp);
            }
        }
    }
    // replace original vector of words with the new one
    words = t_words;
    // loop through all the rest of the characters in the target word
    for(int i=2;i<len;i++){
        // create new temporary vector
        vector<struct coord> new_words;
        // loop through words
        for(coord j: words){
            // calculate the next character based on position and dir
            int offset[2] = {j.r+dirmap[j.dir*2+1], j.c+dirmap[j.dir*2]};
            // check if this character is within bounds and matches the
            // next char in target word
            if(offset[0]<r&&offset[1]<c&&offset[0]>-1&&offset[1]>-1){
                if(letters[offset[0]][offset[1]]==word[i]){
                    //create a new word etc
                    struct coord temp;
                    temp.r=offset[0];temp.c=offset[1];
                    temp.dir=j.dir;
                    temp.turn=j.turn;
                    // push word to temp vector
                    new_words.push_back(temp);
                }
            }
            // if this word has not turned yet, check to see if it
            // can turn during this iteration
            // because directions are stored as ints and not x,y pairs,
            // we can turn the direction by adding or subtracting 4,
            // which is what this totally not cursed for loop does
            if(j.turn)for(int o=j.dir+6;o>j.dir;o-=4){
                // calculate offset
                int offset[2] = {
                    j.r+dirmap[(o%8)*2+1],
                    j.c+dirmap[(o%8)*2]
                };
                // check if character is within bounds and matches target
                if(offset[0]<r&&offset[1]<c&&offset[0]>-1&&offset[1]>-1){
                    if(letters[offset[0]][offset[1]]==word[i]){
                        // etc etc
                        struct coord temp;
                        temp.r=offset[0];temp.c=offset[1];
                        temp.dir=o;
                        temp.turn=false;
                        new_words.push_back(temp);
                    }
                }
            }
        }
        // replace old words with new words
        words = new_words;
    }
    // print out the number of words
    cout << words.size() << '\n';
    // return 1 because c++ is just like that
    return 1;
}
