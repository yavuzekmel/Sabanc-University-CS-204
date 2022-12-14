//
//  SUBook.cpp
//  CS204-THE5
//
//  Created by Ekmel Yavuz on 9.12.2022.
//

#include "SUBook.hpp"
using namespace std;

// --- User ---

// Parameter Constructor
User::User(string name) : userName(name), num_comments(0)
{
    posts = vector<Post *>();
}

// Destructor
User::~User()
{
    for (int i = 0; i < posts.size(); i++)
    {
        delete posts[i];
    }
    posts.clear();
}

// creates a new Post object and adds it to the posts variable
Post &User::createPost(string content)
{

    Post *newPost = new Post(this, content);
    posts.push_back(newPost);

    return *newPost;
}

// return a list of pointers of the posts of the user
vector<Post *> User::getPosts()
{
    return posts;
}

int User::getNumComments()
{

    return num_comments;
}

string User::getName()
{

    return userName;
}

// --- Post ---

// Parameterized Constructor
Post::Post(User *user, string postContent)
{
    postUser = user;
    contentOfPost = postContent;
    comments = vector<Comment *>();
}

// Destructor
Post::~Post()
{
    for (int i = 0; i < comments.size(); i++)
    {
        delete comments[i];
    }
    comments.clear();
}

// return user name of the post
string Post::UserName(User postUser)
{
    return postUser.userName;
}

// adds comment to the post by the user
void Post::addComment(string content, User *commenter)
{
    Comment *comment = new Comment(commenter, this, content);
    this->comments.push_back(comment);
    commenter->num_comments += 1;
}

vector<Comment *> Post::getComments()
{
    return comments;
}

User &Post::getUser()
{
    return *(this->postUser);
}

string Post::getContent()
{
    return contentOfPost;
}

// --- Comment ---

// Parameterized Constructor
Comment::Comment(User *commentUser, Post *commentPost, string commentOfContent)
{
    this->commentUser = commentUser;
    this->commentPost = commentPost;
    contentOfComment = commentOfContent;
}

// Destructor
Comment::~Comment()
{
    commentUser->num_comments -= 1;
}

string Comment::getContent()
{
    return contentOfComment;
}

Post &Comment::getPost()
{
    return *(this->commentPost);
}

User &Comment::getUser()
{
    return *(this->commentUser);
}
