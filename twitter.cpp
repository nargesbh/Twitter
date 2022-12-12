#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include <sstream>
#include <ctime>
using namespace std;
vector<string> insert(string order);
vector<string> select(string);
string pranthesis_delete(string order);
string space_delete(string order);
vector<string> or_combi(vector<string> a , vector<string> b);
vector<string> and_combi(vector<string> a , vector<string> b);
vector<string> split(string a , char c);
vector<string> Delete(string order);
vector<string> Delete_help(vector<string> a , vector<string> b);
bool check_value(string a , string s);
vector<string> Update(string order);
void registering();
void login();
void showTweets();
void myTweet();
vector<string> tweet_file_splitter(string order);
vector<string> comments_file_splitter(string order);
string TimeFormat(char* time);
void writeTweet();
void twitt_operations(string number);
vector<string> order_get(string order);
void likeTweet(string number);
void commentTweet(string number);
void retweet(string number);
void statistic(string number);
void twitt_operations(string number);
void afterLogin();
void quit();
string username;
int main(){
  int choice;
    cout<<"1.if you want to register"<<endl;
    cout<<"2.if you alredy have an account" << endl;
    cout<<"3.quit"<<endl;
    cin>>choice;
    switch(choice){
        case 1 :
            registering();
            break;
        case 2:
            login();
            break;
        case 3:
            quit();
            break;

    }
    return 0;
}
void quit(){
    cout<<"Thanks for using this app"<<endl;
    return;
}
void registering(){
    string name;
    string myusername;
    string password;
    cout<<"enter your name :"<<endl;
    cin>>name;
    cout<<"enter your username : "<<endl;
    cin>>myusername;
    cout<<"enter your password :"<<endl;
    cin>>password;
    string send_to_server = "~$ SELECT FROM users";
    vector<string> server_ans = order_get(send_to_server);
    //find the number of the last ID in the file and fill it in user_number
    string number;
    //age khali bargardoond
    vector<vector<string>> users_lines;
    for(int j=0 ; j<server_ans.size() ; j++){
        users_lines.push_back(split(server_ans[j],' '));
    }
    if(server_ans.size()==0){number="1";}
    else if(server_ans.size()!=0){
        string number2 = users_lines[server_ans.size()-1][0];
            int num;
            stringstream  ss;
            ss << number2;
            ss >> num; 
        for(int j=0 ; j<users_lines.size() ; j++){
            string num_find_help=users_lines[j][0];
            int num_help;
            stringstream ss;
            ss<<num_find_help;
            ss>>num_help;
            if(num_help>num){num=num_help;}
        }  
        num++;
        number= to_string(num);
    }
    string user_number = number ;
    time_t now = time(0);
    char* registration_time = ctime(&now);
    send_to_server="~$ INSERT INTO users VALUES ("+user_number+','+name+','+myusername+','+password+",0,0,"+TimeFormat(registration_time)+");";
    vector<string> check_database = order_get(send_to_server);
    //errors of data base
    if(check_database.size()==1 && check_database[0][11]=='U'){cout<<"your username is already taken please enter another one"<<endl;registering();}
    if(check_database.size()==1 && check_database[0][11]=='L'){cout<<"either your username or your password is too large please enter another pair"<<endl;registering;}
    cout<<"registered"<<endl;
    main();
}
void login(){
    string myusername;
    string password;
    cout<<"Enter your username:";
    cin>>myusername;
    username = myusername;
    cout<<"Enter the password:";
    cin>>password;
    string order="~$ SELECT FROM users WHERE username=="+myusername+" OR password=="+password+";";
    vector<string> ans=order_get(order);
    // string order = "users WHERE username=="+myusername+" OR password=="+password+";";
    // vector<string> ans = select(order);
    vector<vector<string>> user_lines;
    for(int i=0 ; i<ans.size() ; i++){
        user_lines.push_back(split(ans[i],' '));
    }
    bool check=false;
    //check if this pass and username are valid
    for(int j=0 ; j<user_lines.size() ; j++){
        if(myusername==user_lines[j][2] && password==user_lines[j][3]){
            check=true;
            cout<<"loging you in ..."<<endl;
            afterLogin();
        }   
    }
    if(!check){
        cout<<"your username and password doesn't match"<<endl;
        login();
    }
}
void afterLogin(){
    int choice;
    cout<<"After Login Menu:"<<endl;
    cout<<"1.if you want to see all tweets"<<endl;
    cout<<"2.if you want to tweet"<<endl;
    cout<<"3.if you want to see your tweets"<<endl;
    cout<<"4.if you want to logout"<<endl;
    cin>>choice;
    switch(choice){
        case 1:
            showTweets();
            break;
        case 2:
            writeTweet();
            break;
        case 3:
            myTweet();
        case 4:
            main();
            break;
  }
}
void showTweets(){
    cout<<"All tweets :"<<endl;
    cout<<endl;
    //print the twitts and their number and the username who twitted them
    string order="~$ SELECT FROM tweets";
    vector<string> ans = order_get(order);
    // string order = "tweets";
    // vector<string> ans = select(order);
    vector<vector<string>> help_print_tweet;
    for(int i=0 ; i<ans.size() ; i++){
        vector<string> help = tweet_file_splitter(ans[i]);
        help_print_tweet.push_back(help);
    }
    for(int k=0 ; k<help_print_tweet.size() ; k++){
        for(int j=0 ; j<ans.size() ; j++){
            //check if it's a retweet or not
            if (help_print_tweet[k][3]!="0"){
                int retweet_tweet_from ;
                stringstream  ss;
                ss << help_print_tweet[k][3];
                ss >> retweet_tweet_from; 
                cout<<help_print_tweet[k][0]<<" "<<help_print_tweet[k][4]<<" retweeted from "<<help_print_tweet[retweet_tweet_from-1][4]<<" :"<<endl;
                cout<<help_print_tweet[k][6] <<endl;
                cout<<endl;
                break;
            }
            else{
                cout<<help_print_tweet[k][0]<<" "<<help_print_tweet[k][4]<<" tweeted: "<<endl;
                cout<<help_print_tweet[k][6]<<endl;
                cout<<endl;
                break;
            }
        }
    }
    string number;
    cout<<"choose a tweet to like,comment or details or -1 to quit : ";
    cin>>number;
    if(number=="-1"){afterLogin();}
    twitt_operations(number);
}
void writeTweet(){
    string newTweet;
    string values;
    cout<<"enter your tweet :"<<endl;
    cin.ignore();
    getline(cin,newTweet);
    string order="~$ SELECT FROM tweets";
    vector<string> tweets = order_get(order);
    //go find the last twitts' number
    vector<vector<string>> help_print_tweet;
    for(int i=0 ; i<tweets.size() ; i++){
        vector<string> help = tweet_file_splitter(tweets[i]);
        help_print_tweet.push_back(help);
    }
    string number;
    //if the file was empty
    if(help_print_tweet.size()==0){number="1";}
    if(help_print_tweet.size()>0){
    string num_str = help_print_tweet[help_print_tweet.size()-1][0];
    int num_int ;
    stringstream ss;
    ss<<num_str;
    ss>>num_int;
    for(int i=0 ; i<help_print_tweet.size() ; i++){
        string num_find_help=help_print_tweet[i][0];
        int num_help;
        stringstream ss;
        ss<<num_find_help;
        ss>>num_help;
        if(num_help>num_int){num_int=num_help;}
    }
    num_int++;
    number = to_string(num_int);
    }
    if(help_print_tweet.size()==0){number="1";}
    time_t now = time(0);
    char* tweet_time = ctime(&now);
    //stroing the additional data in values
    order="~$ SELECT FROM users WHERE username=="+username+";";
    vector<string> users = order_get(order);
    vector<string> value_count = split(users[0],' ');
    for(int i=0 ; i<value_count.size() ; i++){
        if(i!=4){values+=value_count[i]+',';}
        else if(i==4){
                if(value_count[i]!="0"){ values+=value_count[i]+'-'+number+',';}
                else{values+=number+',';}
                }
    }
    values = values.substr(0,values.size()-1);
    order="~$ INSERT INTO tweets VALUES (" + number + ",0,0,0,"+ username+"," + TimeFormat(tweet_time) +"," +newTweet+");";
    vector<string> ans=order_get(order);
    order="~$ UPDATE users WHERE username=="+username+" VALUES ("+values+");";
    vector<string> ans2=order_get(order);
    afterLogin();
}
void myTweet(){
    string send_to_server;
    cout<<"your tweets :"<<endl;
    cout<<endl;
    send_to_server="~$ SELECT FROM tweets WHERE user=="+username+";";
    vector<string> tweets=order_get(send_to_server);
    vector<vector<string>> help_print_tweet;
    for(int i=0 ; i<tweets.size() ; i++){
        vector<string> help = tweet_file_splitter(tweets[i]);
        help_print_tweet.push_back(help);
    }
    send_to_server="~$ SELECT FROM comments";
    vector<string> comments_file=order_get(send_to_server);
    vector<vector<string>> help_print_comment;
    for(int j=0 ; j<comments_file.size() ; j++){
        help_print_comment.push_back(comments_file_splitter(comments_file[j]));
    }
    for(int j=0 ; j<help_print_tweet.size() ; j++){
        if(help_print_tweet[j][4]==username){
            vector<string> liked_users = split(help_print_tweet[j][2],'-');
            int likes_num = liked_users.size();
            cout << help_print_tweet[j][6]<<endl;
            if(help_print_tweet[j][2]=="0"){likes_num=0;}
            cout<< "likes number: "<<likes_num<<endl;
            if(liked_users[0]!="0"){
                cout<<"users who liked are:"<<endl;
                for(int i=0 ; i<liked_users.size(); i++){
                    cout<<liked_users[i]<<endl;
                }
            }
            vector<string> comments = split(help_print_tweet[j][1],'-');
            int comments_num = comments.size();
            if(help_print_tweet[j][1]=="0"){comments_num=0;}
            cout<<"comments number: "<<comments_num<<endl;
            for(int i=0 ; i<help_print_comment.size() ; i++){
                if(help_print_comment[i][1]==help_print_tweet[j][0]){
                    cout<<"("<<help_print_comment[i][2]<<"): "<<help_print_comment[i][4]<<endl;
                } 
            }
            cout<<endl;
        }
    }
    //print all this username's tweets with their statistics
    afterLogin();
}
void twitt_operations(string number){
    int choice;
    cout<<"1.if you want to like the tweet "<<endl;
    cout<<"2.if you want to comment on this tweet "<<endl;
    cout<<"3.if you want to retweet this tweet"<<endl;
    cout<<"4.if you want to see statistics of this post"<<endl;
    cout<<"5.if you want to go back to After Login Menu"<<endl;
    cin>>choice;
    switch(choice){
        case 1 :
            likeTweet(number);
            break;
        case 2:
            commentTweet(number);
            break;
        case 3:
            retweet(number);
            break;
        case 4:
            statistic(number);
            break;   
        case 5:
            afterLogin();
            break;
    }

}
void likeTweet(string number){
    string order="~$ SELECT FROM tweets WHERE tweet_number=="+number+";";
    //storing all data for UPDATE function
    vector<string> tweets = order_get(order);
    vector<string> tweets_line = tweet_file_splitter(tweets[0]);
    string comments_num=tweets_line[1];
    string liked_users_username=tweets_line[2];
    string retweet_tweet_number=tweets_line[3];
    string user=tweets_line[4];
    string Time=tweets_line[5];
    string tweet=tweets_line[6];
    if (liked_users_username =="0"){liked_users_username=username;}
    else if(liked_users_username!="0"){liked_users_username+="-"+username;}
    string send_to_server="~$ UPDATE tweets WHERE tweet_number=="+ number +" VALUES ("+number+","+comments_num+","+liked_users_username+","+retweet_tweet_number+","+user+","+ Time+","+tweet +");";
    order_get(send_to_server);
    order="~$ SELECT FROM users WHERE username=="+username+";";
    //storing all data for UPDATE function
    vector<string> users = order_get(order);
    vector<string> users_line = split(users[0],' ');
    string user_number=users_line[0];
    string name=users_line[1];
    string username1=users_line[2];
    string password=users_line[3];
    string tweet_numbers=users_line[4];
    string liked_tweets=users_line[5];
    string Time2=users_line[6];
    if(liked_tweets=="0"){liked_tweets=number;}
    else if(liked_tweets!="0"){liked_tweets+='-'+number;}
    send_to_server="~$ UPDATE users WHERE username=="+username+" VALUES ("+user_number+","+name+","+username1+","+password+","+tweet_numbers+","+liked_tweets+","+Time2+");";
    vector<string> ans = order_get(send_to_server);
    for(int j=0 ; j<ans.size() ; j++){
        cout<<ans[j]<<endl;
    }
    cout<<"liked"<<endl;
    twitt_operations(number);
}
void commentTweet(string number){
    cout<<"write the comment:"<<endl;
    string comment;
    cin.ignore();
    getline(cin,comment);
    string send_to_server="~$ SELECT FROM comments";
    //find the number of the last comment 
    vector<string> comments_line_str = order_get(send_to_server);
    vector<vector<string>> comments_file;
    for(int i=0 ; i<comments_line_str.size() ; i++){
        vector<string> help = comments_file_splitter(comments_line_str[i]);
        comments_file.push_back(help);
    }
    string number2;
    int num;
    //if the file was empty
    if(comments_line_str.size()==0){number2="1";}
    else if(comments_line_str.size()!=0){
        number2 = comments_file[comments_line_str.size()-1][0];
            stringstream  ss;
            ss << number2;
            ss >> num; 
        for(int j=0 ; j<comments_line_str.size() ; j++){
            string num_find_help=comments_file[j][0];
            int num_help;
            stringstream ss;
            ss<<num_find_help;
            ss>>num_help;
            if(num_help>num){num=num_help;}
        }  
        num++;
        number2= to_string(num);
    }
    time_t now = time(0);
    char* comment_time = ctime(&now);
    
    send_to_server="~$ INSERT INTO comments VALUES ("+ number2+","+number+','+username+","+ TimeFormat(comment_time) +','+comment+");";
    vector<string> insert_comment = order_get(send_to_server);
    send_to_server="~$ SELECT FROM tweets WHERE tweet_number=="+number+";";
    //finding all values for UPDATE function
    vector<string> tweets = order_get(send_to_server);
    vector<string> tweets_line = tweet_file_splitter(tweets[0]);
    string comments_num=tweets_line[1];
    string liked_users_username=tweets_line[2];
    string retweet_tweet_number=tweets_line[3];
    string user=tweets_line[4];
    string Time=tweets_line[5];
    string tweet=tweets_line[6];
    if (comments_num =="0"){comments_num=number2;}
    else if(comments_num!="0"){comments_num+="-"+number;}
    send_to_server="~$ UPDATE tweets WHERE tweet_number=="+ number +" VALUES ("+number+","+comments_num+","+liked_users_username+","+retweet_tweet_number+","+user+","+ Time+","+tweet +");";
    vector<string> update_tweet=order_get(send_to_server);
    cout<<"commented"<<endl;
    twitt_operations(number);
}
void retweet(string number){
    // string order="tweets";
    string order ="~$ SELECT FROM tweets";
    //reading all lines of tweets file
    vector<string> tweets_line_str = order_get(order);
    vector<vector<string>> tweets_file;
    for(int i=0 ; i<tweets_line_str.size() ; i++){
        vector<string> help = tweet_file_splitter(tweets_line_str[i]);
        tweets_file.push_back(help);
    }
    //finding the number of the last tweet
    string number2;
    int num;
    number2 = tweets_file[tweets_line_str.size()-1][0];
        stringstream  ss;
        ss << number2;
        ss >> num; 
    for(int j=0 ; j<tweets_line_str.size() ; j++){
        string num_find_help=tweets_file[j][0];
        int num_help;
        stringstream ss;
        ss<<num_find_help;
        ss>>num_help;
        if(num_help>num){num=num_help;}
        }  
    num++;
    number2= to_string(num); 
    time_t now = time(0);
    char* retweet_time = ctime(&now);
    order="~$ SELECT FROM tweets WHERE tweet_number=="+number+";";
    //finding the tweet text
    vector<string> tweets = order_get(order);
    vector<string> tweets_line = tweet_file_splitter(tweets[0]);
    string tweet=tweets_line[6];
    order="~$ INSERT INTO tweets VALUES (" + number2 + ',' + "0,0,"+ number+"," +username +','+TimeFormat(retweet_time)+',' +tweet +");";
    vector<string> insert_vec = order_get(order);
    twitt_operations(number);
}
void statistic(string number){
        //show likes and comments
        string send_to_server="~$ SELECT FROM tweets WHERE tweet_number=="+number+";";
        vector<string> tweets = order_get(send_to_server);
        vector<vector<string>> help_print_tweet;
        for(int i=0 ; i<tweets.size() ; i++){
            vector<string> help = tweet_file_splitter(tweets[i]);
            help_print_tweet.push_back(help);
        }
        send_to_server="~$ SELECT FROM comments";
        vector<string> comments_file=order_get(send_to_server);
        vector<vector<string>> help_print_comment;
        for(int j=0 ; j<comments_file.size() ; j++){
            help_print_comment.push_back(comments_file_splitter(comments_file[j]));
        }
        for(int j=0 ; j<help_print_tweet.size() ; j++){
            if(help_print_tweet[j][0]==number){
                cout<<"username :"<<help_print_tweet[j][4]<<endl;
                vector<string> liked_users = split(help_print_tweet[j][2],'-');
                int likes_num = liked_users.size();
                cout <<"tweet :" <<help_print_tweet[j][6]<<endl;
                cout<< "likes number: "<<likes_num<<endl;
                if(liked_users[0]!="0"){
                    cout<<"users who liked are:"<<endl;
                    for(int i=0 ; i<liked_users.size(); i++){
                        cout<<liked_users[i]<<endl;
                    }
                }
                vector<string> comments = split(help_print_tweet[j][1],'-');
                int comments_num = comments.size();
                cout<<"comments number: "<<comments_num<<endl;
                for(int i=0 ; i<help_print_comment.size() ; i++){
                    if(help_print_comment[i][1]==help_print_tweet[j][0]){
                        cout<<"("<<help_print_comment[i][2]<<"): "<<help_print_comment[i][4]<<endl;
                    } 
                }
                cout<<endl;
            }
        }
       twitt_operations(number);
}
vector<string> order_get(string order){
    if(order.substr(0,3)=="~$ "){
        if(order.substr(3,12)=="INSERT INTO ") {
            return insert(order.substr(15,order.size()-15));
        }
        if(order.substr(3,12)=="SELECT FROM "){
            return select(order.substr(15,order.size()-15));
        }
        if(order.substr(3,12)=="DELETE FROM "){
            return Delete(order.substr(15,order.size()-15));
        }
        if(order.substr(3,7)=="UPDATE "){
            return Update(order.substr(10,order.size()-10));
        }
        else {
            vector<string> error ={"syntax error : such command doen't exist in this database"};
            return error;
            }
    }
    else{
      vector<string>  error2 = {"syntax error :your order doesn't start with ~$ "};
      return error2;
    }

}
vector<string> insert(string order){
    string tableName;
    string value;
    vector<string> error;
    int i=0;
    //find table name
    while(order[i]!=' '){
        tableName+=order[i];
        i++;
    }
    i++;
    while(order[i]!=' '){
        value+=order[i];
        i++;
    }
    //check errors
    if (value!="VALUES"){
        cout<<"Syntax error:the keyword 'VALUES' isn't in your order"<<endl;
        return error; 
    }
    i++;
    order=order.substr(i,order.size()-i);
    if( order[0]!='(' || order[order.size()-2]!=')'){
        error.push_back("Syntax error:you need to have paranthesis befor and after values");
        return error;
        }
    if(order[order.size()-1]!=';') {
        cout<<"Syntax error:you need to have ';' at the end of your order";
        return error;
        }
        //reading scehma
    vector<string> values;
    values=split(order.substr(1,order.size()-3),',');
    ifstream schema("schema.txt");
    string readFile;
    bool check1=false;
    i = 0;
    while(!schema.eof()){
        getline(schema,readFile);
        //find table in schema
        if(readFile==tableName){
            check1 = true;
            while(readFile!=""){
            getline(schema,readFile);
            vector<string> fileLine = split(readFile , ' ');
            ofstream make_table_file((tableName+".txt").c_str(),ios::app);
            make_table_file.close();
            //check if its unique
            if(fileLine.size()==3){
                bool check2 = check_value(values[i] , fileLine[2]);
                if(!check2){
                    error.push_back("Data error L: the values you entered doesn't match schema.txt");
                    return error;
                }
                //if schema is unique check the validity of values 
                ifstream tablefile((tableName+".txt").c_str());
                string line;
                while(!tablefile.eof()){
                    getline(tablefile,line);
                    vector<string> check_help;
                    check_help=split(line,' ');
                    if(check_help[i]==values[i]) {
                        if(check_help[i]!="0"){error.push_back("Data error U: one of you values is unique in schema.txt but you're choosing an already-used value for it");
                        return error;}
                        }
                }
                tablefile.close();
            }
            //if schema wasn't unique
            if(fileLine.size()==2){
                bool check2 = check_value(values[i] , fileLine[1]);
                if(!check2){
                    error.push_back("Data error L: the values you entered doesn't match schema.txt");
                    return error;                    
                }
            }
            if(i>values.size()){
                error.push_back("Data error : the number of the values you entered is not enough");
                return error;
            }
            i++;
        }
    }
}
    if(!check1){
        error.push_back("Data error : there is no such table name in your database");
        return error;
    }
    schema.close();
    i--;
    if(i!=values.size()){
        error.push_back("Data error :the number of the values you entered doesn't match schema.txt");
        return error;
    }
    //adding to the file
    ofstream writefile((tableName+".txt").c_str(),ios::app);
    for(int k=0;k<values.size();k++){
        writefile<<values[k];
        if(k!=values.size()-1)writefile<<' ';
    }
    writefile<<endl;
    writefile.close();
    return error;
}
vector<string> select(string order){
    // string order="photos WHERE (name==narges);";
    //order="photos"
    string tableName;
    string schema_exp;
    string table_val;
    string where;
    vector<string> ans;
    vector<string> error ;
    string help_open;//store first characters of the string to help for recersive call
    string check_all_retrun = space_delete(order);
    //checks the type of the order 
    bool check_space=false;
    for(int k=0 ; k<check_all_retrun.size() ; k++){
        if(order[k]==' '){
            check_space=true;
        }
    } 
    //if it should send all data 
    if(!check_space){
        tableName=check_all_retrun;
        vector<string> table_lines;
        ifstream tablefile((tableName+".txt").c_str());
        string readTableLine;
        while(!tablefile.eof()){
            getline(tablefile,readTableLine);
            if(readTableLine!=""){table_lines.push_back(readTableLine);}
                }
            return table_lines;
    }
    int i=0;
    while(order[i]!=' '){
        tableName+=order[i];
        i++;
    }
    i++;
    // cout<<"table name:"<<tableName<<endl;
    while(order[i]!=' '){
        where+=order[i];
        i++;
    }
    // cout<<"value :"<<value<<endl;
    if (where!="WHERE"){
        cout<<"Syntax error:the keyword 'WHERE' isn't in your order"<<endl;
        return error; 
    }
    i++;
    help_open = order.substr(0,i);
    //order==all values
    order=order.substr(i,order.size()-i-1);//1 is for deleting ';'
    i=0;
    bool check_successor=false;
    //check if it has successor
    for(int k=0 ; k<order.size()-2 ; k++){
        if( ( order[k]=='O' &&  order[k+1] == 'R' ) || ( order[k]=='A' && order[k+1]=='N' && order[k+2] =='D' ) ){
            check_successor = true;
        }
    }
    if(!check_successor){//(a OR b) a OR b
        order = pranthesis_delete(order);
        while(order[i]!='=' && order[i]!='!'){
            schema_exp+=order[i];
            i++;
        }
        i+=2;
        while(order[i]!=';' && order[i]!=' ' && i!=order.size() ){
            table_val+=order[i];
            i++;
        }
        //reading schema
        ifstream schema("schema.txt");
        string readFile;
        bool checkTable=false;
        bool checkElement=false;
        bool checkFind=false;
        i=0;
        while(!schema.eof()){
            getline(schema,readFile);
            //finding table name in schema
            if(tableName==readFile){
                checkTable = true;
                while(readFile!=""){
                    getline(schema,readFile);
                    vector<string> schema_line = split(readFile,' ');
                    //finding the index of the expression of the order
                    if(schema_line[0]==schema_exp){
                        checkElement=true;
                        ifstream tablefile((tableName+".txt").c_str());
                        string readTableLine;
                        while(!tablefile.eof()){
                            getline(tablefile,readTableLine);
                            vector<string> table_line=split(readTableLine,' ');
                            //matching the order with table file
                            if(table_line[i]==table_val){
                                checkFind=true;
                                ans.push_back(readTableLine);
                            }
                        }
                    }
                    i++;
                }
                if(!checkElement){
                    error.push_back("Data error : this table doesn't have such element in it");
                    return error;
                }
            }
        }
        if(!checkTable){
            error.push_back("Data error :there isn't any table with this name in schema.txt");
            return error;
        }
        if(!checkFind){
            error.push_back("Data error : couldn't find the data you wanted ");
            return error;
        }
        return ans; 
    }
            // string order="~$ SELECT FROM photos WHERE (name==narges OR username==mahyar80) AND (id==3 AND id==5) ;";
    // string order="photos WHERE name==narges;";
    // string order="photos WHERE (name==narges OR id==2) AND username==mahyar80;";
    else{
        //be saresh help_open ezafe kon be tahesh ';'
        order = pranthesis_delete(order);
        //az avval ta qabl az AND harchi space ezafe bood hazf mikonam bad midamesh be tabe
        //az bade and ta akhar spacaye ezafe saro tahesho hazf mikonam behesh ';' ezafe mikonam midam be tabe
        string before_successor;
        string after_successor;
        int counter=0;
        //(a AND B )OR (b OR c)
        for(int i=0 ; i<order.size()-2 ; i++){
            //peyda kardan avvalin operator azad
            if(order[i]=='('){
                counter++;
            }
            if(order[i]==')'){
                counter--;
            }
            //recursive call
            if(( order[i]=='O' &&  order[i+1] == 'R' ) && counter==0){
                before_successor = help_open + space_delete(order.substr(0,i-1))+";";
                after_successor = help_open + space_delete(order.substr(i+2 , order.size()-i-2))+";";
                vector<string> befor_or = select(before_successor);
                vector<string> after_or = select(after_successor);
                vector<string> ans = or_combi(befor_or , after_or);
                return ans;
            }
            if( ( order[i]=='A' && order[i+1]=='N' && order[i+2] =='D' ) && counter==0 ){
                before_successor =help_open + space_delete(order.substr(0,i-1))+";";
                after_successor =help_open + space_delete(order.substr(i+4 , order.size()-i-2))+";";  
                vector<string> befor_and = select(before_successor);
                vector<string> after_and = select(after_successor);
                vector<string> ans = and_combi(befor_and , after_and);
                return ans;
            }
        }

    }
    return ans;
}
vector<string> Delete(string order){
    string tableName;
    vector<string> error;
    int i=0;
    //check syntax
    while(order[i]!=' '){
        tableName+=order[i];
        i++;
    }
    //selecting the given lines
    vector<string> ans = select(order);
    if(ans[0].substr(0,6)=="Syntax" || ans[0].substr(0,4)=="Data"){
        return ans;
    }
    //reading table file and storing all the data
    vector<string> table_lines;
    ifstream tablefile((tableName+".txt").c_str());
        string readTableLine;
        while(!tablefile.eof()){
            getline(tablefile,readTableLine);
            if(readTableLine!=""){table_lines.push_back(readTableLine);}
                }
                //select the data and delete it from our file vector
    vector<string> writeFile = Delete_help(table_lines,ans);
    //writing the file again
    ofstream writefile2(tableName+".txt");
    for(int k=0;k<writeFile.size();k++){
        writefile2<<writeFile[k]<<endl;
    }
    writefile2.close();
    return error;
}
vector<string> Update(string order){
        //string order ="users WHERE username=="narges" VALUES ();";
        bool check_value_keyword=false;
        int V_index;
        string tableName;
        vector<string> error;
        int i=0;
        //checking the syntax
        while(order[i]!=' '){
                tableName+=order[i];
                i++;
        }
        for(int i=0 ; i<order.size()-5 ; i++){
                if(order[i]=='V' && order[i+1]=='A' && order[i+2]=='L' && order[i+3]=='U' && order[i+4]=='E' && order[i+5]=='S'){
                        check_value_keyword=true;
                        V_index=i;
                }
        }
        if(!check_value_keyword){
                cout<<"Syntax error : your order doesn't have the keyword 'VALUES' "<<endl;
                return error;
        }
        //selecting the line
        string help_from_select = space_delete(order.substr(0,V_index+1));

        vector<string> select_output = select(help_from_select);
        string select_error_check = select_output[0];
        if(select_error_check.substr(0,6)=="Syntax" || select_error_check.substr(0,4)=="Data"){
                cout<<select_error_check<<endl;
                return error;
        }
        //checking syntax
       order = order.substr(V_index+7 , order.size() - V_index - 7) ;
           if( order[0]!='(' || order[order.size()-2]!=')'){
        cout<<"Syntax error:you need to have paranthesis befor and after values"<<endl;
        return error;
        }
        if(order[order.size()-1]!=';') {
                cout<<"Syntax error:you need to have ';' at the end of your order";
                return error;
                }
        vector<string> values;
        values=split(order.substr(1,order.size()-3),',');
        //reading schema and checking the values with new ones
        ifstream schema("schema.txt");
        string readFile;
        bool check1=false;
        i = 0;
        while(!schema.eof()){
                getline(schema,readFile);
                if(readFile==tableName){
                check1 = true;
                while(readFile!=""){
                getline(schema,readFile);
                vector<string> fileLine = split(readFile , ' ');
                ofstream make_table_file((tableName+".txt").c_str(),ios::app);
                make_table_file.close();
                //find if it should be unique
                if(fileLine.size()==3){
                    //check if they have the same type
                        bool check2 = check_value(values[i] , fileLine[2]);
                        if(!check2){
                        error.push_back("Data error : the values you entered doesn't match schema.txt");
                        return error;
                        }
                        ifstream tablefile((tableName+".txt").c_str());
                        string line;
                        while(!tablefile.eof()){
                        getline(tablefile,line);
                        vector<string> check_help;
                        check_help=split(line,' ');
                        // if(check_help[i]==values[i]) {
                        //         error.push_back("Data error : one of you values is unique in schema.txt but you're choosing an already-used value for it");
                        //         return error;
                        //         }
                        }
                        tablefile.close();
                }
                if(fileLine.size()==2){
                        bool check2 = check_value(values[i] , fileLine[1]);
                        if(!check2){
                        error.push_back( "Data error : the values you entered doesn't match schema.txt");
                        return error;                    
                        }
                }
                if(i>values.size()){
                        error.push_back("Data error : the number of the values you entered is not enough");
                        return error;
                }
                i++;
                }
        }
        }
        if(!check1){
                error.push_back("Data error : there is no such table name in your database");
                return error;
        }
        schema.close();
        i--;
        if(i!=values.size()){
                error.push_back("Data error :the number of the values you entered doesn't match schema.txt");
                return error;
        }
        //storing the file in a vector
        ifstream tablefile((tableName+".txt").c_str());
        string readTableLine;
        vector<string> all_lines;
        while(!tablefile.eof()){
                getline(tablefile,readTableLine);
                if(readTableLine!=""){ all_lines.push_back(readTableLine);}
                        }
        vector<string> final_ans = Delete_help(all_lines,select_output);
        //writing it with updated values
        ofstream writefile2(tableName+".txt");
        for(int k=0;k<final_ans.size();k++){
        writefile2<<final_ans[k]<<endl;
        }
        for(int k=0;k<values.size();k++){
        writefile2<<values[k];
        if(k!=values.size()-1)writefile2<<' ';
        }
        writefile2<<endl;
        writefile2.close();
        return error;
}
string pranthesis_delete(string order){
    int counter=0;
    for(int i=0 ; i<order.size() ; i++){
        if(order[i]=='('){
            counter ++;
        }
        if(order[i]==')'){
            counter--;
        }
        if(counter==0 && i!=order.size()-1){
            return order;
        }
        if(counter==0 && i==order.size()-1 && order[i]==')'){
                return order.substr(1,order.size()-2);
        }
    }
    return order;
}
string space_delete(string order){
    int space_before=0;
    int space_after=0;
    int i=0;
    if (order[i]==' '){
        i++;
        space_before++;
        while(order[i]==' '){
            space_before++;
            i++;
        }
    }
    i=order.size()-1;
    if(order[i]==' '){
        space_after++;
        i--;
        while(order[i]==' '){
            space_after++;
            i--;
        }
    }
    return order.substr(space_before , order.size()- space_before - space_after );

}
vector<string> or_combi(vector<string> a , vector<string> b){
    bool check=true;
    for(int i=0 ; i<a.size() ; i++){
        for(int j=0 ; j<b.size() ; j++){
            if(a[i]==b[j]){
                check=false;
            }
        }
        if(check){b.push_back(a[i]);}
        check=true;
    }
    return b;
}
vector<string> and_combi(vector<string> a , vector<string> b){
    bool check=false;
    vector<string> ans;
    for(int i=0 ; i<a.size() ; i++){
        for(int j=0 ; j<b.size() ; j++){
            if(a[i]==b[j]){
                ans.push_back(a[i]);
            }
        }
    }
    return ans;
}
vector<string> split(string a , char c){
    vector<string> values;
    string help;
    for(int i=0 ; i<a.size() ; i++ ){
        if(a[i]!=c){
            help+=a[i];
        }
        else{
            values.push_back(help);
            help="";
        }
    }
    values.push_back(help);
    return values;
}
vector<string> Delete_help(vector<string> a , vector<string> b){
    //deletes all intersections of b in a
    vector<string> answer;
    bool check = false;
    for(int i=0 ; i<a.size() ; i++){
        for(int j=0 ; j<b.size() ; j++){
            if(a[i] == b[j]){
                check=true;
            }
        }
        if(!check){
            answer.push_back(a[i]);
        }
        check=false;
    }
    return answer;
}
bool check_value(string a , string s){
    // cout<<"string 1:"<<a<<endl;
    // cout<<"string 2 :"<<s<<endl;
    if(s=="TIMESTAMP"){
        return true;
    }
    if(s=="BOOLEAN"){
        if(a=="true" || a=="false"){
            return true;
        }
    // cout<<"1"<<endl;
    return false;
}
    if(s=="INTEGER"){
        string help="0987654321";
        bool int_check=false;
        for(int i=0 ; i<a.size() ; i++){
            for(int j=0 ; j<10 ; j++){
                if (a[i]==help[j]){int_check=true;}
            }
            if(int_check==false){return false;}
            else{int_check=false;}
        }
        return true;
    }
    // cout<<"2"<<endl;
    //INTEGER[100] 1-2-3-4
    if(s.size()>7 && s.substr(0,7)=="INTEGER"){
        // cout<<"size:"<<s.size()<<endl;
        // cout<<"L"<<endl;
        s=s.substr(8,s.size()-9);
        stringstream change(s);
        int schema_int=0;
        change >> schema_int;
        vector<string> int_arr=split(a,'-');
        int val_vec_size = int_arr.size();
        if(val_vec_size > schema_int ){
            return false;
        }
        for(int k=0 ; k<val_vec_size ; k++){
            if(check_value(int_arr[k],"INTEGER")==false){
                return false;
            }
        }
        return true;
    }
    // cout<<"3"<<endl;
    if(s.size()>4 && s.substr(0,4)=="CHAR"){
        s=s.substr(5,s.size()-6);
        stringstream change(s);
        int schema_int=0;
        change >> schema_int;
        // cout<<"schema size:"<<schema_int<<endl;
        // cout<<"a.size():"<<a.size()<<endl;
        if(schema_int < a.size()){
            return false;
        }
        return true;
    }
    return true;
}
vector<string> tweet_file_splitter(string order){
    vector<string> tweetfile_line;
    string help;
    int c =0;
    for(int i=0 ; i<order.size() ; i++){
        if(order[i]!=' '){
            help+=order[i];
        }
        else{
            c++;
            tweetfile_line.push_back(help);
            help="";
            if(c==6){
                help = order.substr(i+1,order.size()-i-1);
                tweetfile_line.push_back(help);
                break;
            }
        }
    }
    return tweetfile_line;
}
vector<string> comments_file_splitter(string order){
    vector<string> commentfile_line;
    string help;
    int c =0;
    for(int i=0 ; i<order.size() ; i++){
        if(order[i]!=' '){
            help+=order[i];
        }
        else{
            c++;
            commentfile_line.push_back(help);
            help="";
            if(c==4){
                help = order.substr(i+1,order.size()-i-1);
                commentfile_line.push_back(help);
                break;
            }
        }
    }
    return commentfile_line;  
}
string TimeFormat(char* time){
   string time2 = "";
   int i=0;
   while (i < 24)
   {
        if(time[i] != ' '){
            time2 += time[i];
            i++;
        }
        else if(time[i]==' '){
            time2 += '/';
            while(time[i]==' '){
                i++;
            }
        }
   }
   return time2;
}