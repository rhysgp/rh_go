# A Go server in C++

## Purpose
OGS (online-go.com) is a bit flaky. This is just to play around with some ideas.

## Why C++?
Partly because I'm interested in C++, and partly because I want this to run 
efficiently. The lower the footprint the better.

## What will it do?
Initially, it will:
 - Store users, allowing them to find one another to play games of Go.
 - Store the games themselves and their outcome.
 - Allow playing against a local AI (e.g. katago), probably via docker

Later, it will:
 - Calculate and store users' ratings.
 - Manage tournaments
 - Manage ladders

Then, it will:
 - allow users to play non-local AI
 - store AI analyses of games

## How will it differentiate itself from other providers?
 - It will focus on connecting people
 - It will focus on an easy-to-use UI
 - It will focus on enabling local playing of AI

## What backend will you use (i.e. database)?
I think it will be PostgreSQL. But, I'm going to start with an in-memory store
for now, because I want to delay having to deal with the database. In the back
of my mind I'm thinking, "I wonder if I can get an AI to generate the data
access layer?" We'll see....