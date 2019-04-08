#include<cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Goal{
    string away;
    int minute;
    int matchID;
    Goal *prev = NULL;
    Goal *next = NULL;
};

struct Footballer{
    string name;
    string team;
    Goal *GoalHead = NULL;
    Footballer *next = NULL;
};
void scoredHalf(Footballer *head, ofstream& out);
Footballer* findFootballer(string name, Footballer *head);
void addFootballer(Footballer *f,Footballer **head, Footballer **tail);
void writeListOfFootballers(Footballer *head, ofstream &out);


int main(int argc, char *argv[]){

    string input=argv[1];
    string operations =argv[2];
    string output =argv[3];

    std::ifstream file(input.c_str());
    ofstream out;
    out.open (output.c_str());
    std::string line;
    std::string word;
    Footballer *head=NULL;
    Footballer *tail=NULL;
    vector<string> allLines;
    vector<string> lineWord;
    /*read file into a vector*/
    while (std::getline(file, line)) {
        allLines.push_back(line);
    }
    /*sort lines*/
    sort(allLines.begin(), allLines.end());
    /*iterate over the file*/
        for(unsigned i = 0; i < allLines.size(); i++){
                line = allLines.at(i);
            stringstream stream(line);
            /*split string by comma*/
            while( getline(stream, word, ',') ){
                lineWord.push_back(word);
            }

        if(findFootballer(lineWord[0], head) == NULL){
    /*create new footballer*/
            Footballer *f=new Footballer();
            f->name = lineWord[0];
            f->team = lineWord[1];
            Goal *g = new Goal();

            g->away = lineWord[2];
            g->minute = std::atoi(lineWord[3].c_str());
            g->matchID = std::atoi(lineWord[4].c_str());
            g->next = NULL;
            f->GoalHead = g;
        addFootballer(f, &head, &tail);
        }else if(findFootballer(lineWord[0], head)){

            Footballer *f = findFootballer(lineWord[0], head);
            Goal *g = new Goal();
            g->away = lineWord[2];
            g->minute = std::atoi(lineWord[3].c_str());
            g->matchID = std::atoi(lineWord[4].c_str());

            // just 1 goal
            if(f->GoalHead->next==NULL)
            {
                f->GoalHead->next=g;
                g->prev=f->GoalHead;

            }
            //more than one goal
            else
            {
                Goal* gp=f->GoalHead;
                while(gp->next!=NULL)
                {
                    gp=gp->next;
                }
                gp->next=g;
                g->prev=gp;

            }

        }
        lineWord.clear();
        }
    scoredHalf(head, out);
    writeListOfFootballers(head, out);
    out.close();
  return 0;
}

void scoredHalf(Footballer *head, ofstream &out){
    out << "1)THE MOST SCORED HALF" << endl;
    Footballer *f = head;
    int first = 0;
    int second = 0;
    int count = 0;
    int max = 0;
    vector<string> maxName;
    vector<string> hattrick;
    vector<string> teamNames;
    vector<int> matches;
    while(f)
    {
        //cout << f->name << endl;
        while(f->GoalHead){

            matches.push_back(f->GoalHead->matchID);

            if(f->GoalHead->minute <=45){

                first = first + 1;
            }else{
                second = second + 1;
            }

            count = count +1;
            if ( std::find(teamNames.begin(), teamNames.end(), f->team) != teamNames.end() ){

            }else{
                teamNames.push_back(f->team);
            }

           /* if ( std::find(teamNames.begin(), teamNames.end(), f->GoalHead->away) != teamNames.end() ){

            }else{
                teamNames.push_back(f->GoalHead->away);
            }*/

            f->GoalHead = f->GoalHead->next;
        }
        sort(matches.begin(), matches.end());
        for(unsigned i = 0; i < matches.size(); i++){
                if(i+2 < matches.size()){
                    if(matches[i] == matches[i+2]){

                        hattrick.push_back(f->name);
                    }
                }

        }
        matches.clear();
        if(count > max){
            max = count;
            if(maxName.size() > 0)
                maxName.clear();
            maxName.push_back(f->name);
        }else if(count == max){
             maxName.push_back(f->name);
        }
        count = 0;
        f=f->next;
        //cout<< hattrick.size()<< endl;
    }

    if(first > second){
        out << "0" << endl;
    }else
        out << "1" << endl;
    out << "2)GOAL SCORER" << endl;
    for(unsigned j = 0; j < maxName.size(); j = j+1){
        out << maxName[j] << endl;
    }
    out << "3)THE NAMES OF FOOTBALLERS WHO SCORED HAT-TRICK" << endl;
    for(unsigned j = 0; j < hattrick.size(); j = j+1){
        out << hattrick[j] << endl;
    }
    out << "4)LIST OF TEAMS" << endl;
    for(unsigned j = 0; j < teamNames.size(); j = j+1){
        out << teamNames[j] << endl;
    }


}

Footballer* findFootballer(string name, Footballer *head){

    //if linked list is empty return null
    if(head==NULL)
        return NULL;
    // if first pointer of  footballer linked list has same name with name that given argument, return pointer
    if(name.compare(head->name)==0)
        return head;

    Footballer *f=head;
    while(f->next!=NULL)
    {
        f=f->next;
        if(name.compare(f->name)==0) // if name (argument) and name of footballer f is equal
            return f;

    }
    return NULL;

}

void addFootballer(Footballer *f, Footballer **head, Footballer **tail){

    if(*head==NULL){
        *head=f;
        //cout<<"head in add:"<<head<<"\n\n";
        //cout<<"f in add:"<<f<<"\n\n";
        *tail=f;
    }
    else{
       (*tail)->next=f;
        *tail=f;
    }

    return;

}

void writeListOfFootballers(Footballer *head, ofstream &out)
{
    out<< "5)LIST OF FOOTBALLERS\n";
    //if head is null
    if(head==NULL)
        cout<< "No football players yet.\n";

    else
    {
        Footballer *f=head;
        while(f)
        {
            out<<f->name<<"\n";

                /*while(f->GoalHead){
                    cout << f->GoalHead->matchID << endl;
                    f->GoalHead = f->GoalHead->next;
                }*/


           /* cout<<f->GoalHead->away<<"\n" << endl;*/
            f=f->next;
        }
    }
}

