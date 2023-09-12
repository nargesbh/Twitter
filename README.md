# Twitter Project

## Introduction

The Twitter Project is a command-line application developed in C++ that simulates basic Twitter-like functionality. It allows users to perform various actions, such as user registration, logging in, posting tweets, liking tweets, commenting on tweets, and more. This project is designed to manage tweets, comments, and user data in a rudimentary database.

## Features

### User Registration
- Users can register with a name, username, and password.
- User data is securely stored for future logins.

### User Login
- Registered users can log in to their accounts.
- Authentication ensures the security of user accounts.

### Tweet Posting
- Users can post tweets with text content.
- Share your thoughts and updates with your followers.

### Like Tweets
- Users can like tweets to express their appreciation.
- See how many likes each tweet has received.

### Comment on Tweets
- Users can comment on tweets to engage in discussions.
- Read and respond to comments on your own tweets.

### View Tweets
- Users can view all tweets posted on the platform.
- See the latest updates from other users.

### Tweet Statistics
- Users can view statistics for a specific tweet.
- Check the number of likes and comments on a particular tweet.

### Retweeting
- Users can retweet tweets to share interesting content.
- Spread tweets you find engaging to your followers.

### Basic Database
- The project manages user data, tweets, and comments using basic text files.
- User information, tweets, and comments are stored securely in text files within the project directory.


## Database Operations
### Posting Tweets
- When a user posts a tweet, the tweet content is added to the respective user's tweet file in the database.
- Each tweet is associated with a timestamp, allowing users to view tweets chronologically.
### Liking Tweets
- When a user likes a tweet, the tweet's like count is updated in the database.
- Users can view the number of likes on each tweet.
### Commenting on Tweets
- Users can comment on tweets, and their comments are appended to the respective tweet's comment section in the database.
- Comments are associated with a timestamp for reference.
### Retrieving and Displaying Data
- When users view tweets, the application reads tweet and comment data from the database files.
- The data is presented to users in a user-friendly format.
### Updating User Information
- User registration and login details are managed in user data files in the database.
- User passwords are securely hashed before storage to enhance security.

## Database

The Twitter Project uses a basic text-based database to store user information, tweets, and comments. Data is stored in text files within the project directory, ensuring that user data is accessible and persistent across sessions.





