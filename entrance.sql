create database if not exists ACS;

use ACS;

create table if not exists user_Table(
    user_name varchar(32),
    user_card_id varchar(32) primary key,
    user_address varchar(128),
    phone_num varchar(16)
);

create table if not exists user_Access(
    user_name varchar(32),
    user_card_id varchar(32),
    user_address varchar(128),
    phone_num varchar(16),
    access_time timestamp
);

create table if not exists Trespassing(
    card_id varchar(32),
    into_time timestamp
);

create table if not exists administrator(
    admin_name varchar(32) primary key,
    admin_pwd varchar(32)
);
