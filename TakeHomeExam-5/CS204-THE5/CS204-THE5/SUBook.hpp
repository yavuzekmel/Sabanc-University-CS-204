//
//  SUBook.hpp
//  CS204-THE5
//
//  Created by Ekmel Yavuz on 9.12.2022.
//

#ifndef SUBook_hpp
#define SUBook_hpp

#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

class Post;
class Comment;

class User {
    
    friend class Post;
    friend class Comment;
    
    
public:
    
    User(string name);
    ~User();
    
    Post& createPost(string content);
    vector <Post*> getPosts();
    int getNumComments();
    string getName();

private:
    
    string userName;            // The users's name as a string.
    vector <Post*> posts;        // A list of all the posts created by the user.
    int num_comments;       // Number of commments that the user made on all posts.
    
};


class Post {
    
    friend class User;
    friend class Comment;
    
public:
    
    Post();
    Post(User* user , string postContent);
    ~Post();
    
    void addComment(string content, User* commenter);
    vector<Comment*> getComments();
    
    string UserName(User postUser);
    
    User&  getUser();
    string getContent();
    
    
private:
    
    User* postUser;      //  The user who made the comment.
    string contentOfPost;                 //  The text content of the comment.
    vector <Comment*> comments;            //  A list of all comments on the post.
    
};


class Comment {
        
    friend class User;
    friend class Post;
    
public:
    
    Comment(User* commentUser, Post* commentPost, string contentOfComment);
    ~Comment();
    
    User& getUser();
    Post& getPost();
    string getContent();
    
    
private:
    
    User* commentUser;                                     // The user who made the comment.
    Post* commentPost;                                     // The post the comment is on.
    string contentOfComment;                                // The text content of the comment.
   
    
};

#endif /* SUBook_hpp */
