DROP DATABASE sgpadb;
CREATE DATABASE sgpadb;
USE sgpadb;

CREATE TABLE demo_node (row_id int not null primary key auto_increment,
component varchar(20), version varchar(12), idtype varchar(20),
os varchar(10), expire_days int, max_issue int);

CREATE TABLE demo_node_data (row_id int not null primary key auto_increment,
component varchar(20), version varchar(12), idtype varchar(20), 
os varchar(10), issue_date varchar(20), 
expire_date varchar(20), remaining int, email varchar(256),
ethernet varchar(15), hostname varchar(256), ipaddress varchar(20), inet6 varchar(30), 
username varchar(32), macintosh varchar(20), hostid varchar(20), country varchar(5), vsn varchar(20),
vendor varchar(256), any varchar(256), metered varchar(32), iphone varchar(64),
android varchar(64), blackberry varchar(64));

CREATE TABLE demo_float (row_id int not null primary key auto_increment,
component varchar(20), version varchar(12), idtype varchar(20),
os varchar(10), server varchar(128), port varchar(20), count int, expire_days int, 
max_issue int);

CREATE TABLE demo_float_data (row_id int not null primary key auto_increment,
component varchar(20), version varchar(12), idtype varchar(20), 
os varchar(10), server varchar(128), port varchar(20), count int,
issue_date varchar(20), expire_date varchar(20), remaining int, email varchar(256),
ethernet varchar(15), hostname varchar(256), ipaddress varchar(20),
inet6 varchar(30), username varchar(32), macintosh varchar(20), 
hostid varchar(20), country varchar(5), vsn varchar(20),
vendor varchar(256), any varchar(256), metered varchar(32), iphone varchar(64),
android varchar(64), blackberry varchar(64));


CREATE TABLE paid_node (row_id int not null primary key auto_increment,
cust varchar(256), component varchar(20), version varchar(12),
idtype varchar(20), os varchar(10), expire_days int, max_issue int);

CREATE TABLE paid_node_data (row_id int not null primary key auto_increment,
cust varchar(256), component varchar(20), version varchar(12),
idtype varchar(20), os varchar(10), 
issue_date varchar(20), expire_date varchar(20), remaining int, 
email varchar(256), ethernet varchar(15), hostname varchar(256), 
ipaddress varchar(20), inet6 varchar(30), username varchar(32), 
macintosh varchar(20), hostid varchar(20), country varchar(5), 
vsn varchar(20), vendor varchar(256), any varchar(256), metered varchar(32), 
iphone varchar(64), android varchar(64), blackberry varchar(64));

CREATE TABLE paid_float (row_id int not null primary key auto_increment,
cust varchar(256), component varchar(20), version varchar(12), idtype varchar(20),
os varchar(10), server varchar(128), port varchar(20), count int, expire_days int, 
max_issue int);

CREATE TABLE paid_float_data (row_id int not null primary key auto_increment,
cust varchar(256), component varchar(20), version varchar(12), idtype varchar(20), 
os varchar(10), server varchar(128), port varchar(20), count int,
issue_date varchar(20), expire_date varchar(20), remaining int, email varchar(256),
ethernet varchar(15), hostname varchar(256), ipaddress varchar(20),
inet6 varchar(30), username varchar(32),
macintosh varchar(20), hostid varchar(20), country varchar(5), vsn varchar(20),
vendor varchar(256), any varchar(256), metered varchar(32), iphone varchar(64),
android varchar(64), blackberry varchar(64));

insert into demo_node(component,version,idtype,os,expire_days,max_issue) values('monitor','5.0','any','mac32',30,10);
insert into demo_node(component,version,idtype,os,expire_days,max_issue) values('monitor','5.0','any','mac64',30,10);
insert into demo_node(component,version,idtype,os,expire_days,max_issue) values('monitor','5.0','any','win32',30,10);
insert into demo_node(component,version,idtype,os,expire_days,max_issue) values('monitor','5.0','any','win64',30,10);
insert into demo_node(component,version,idtype,os,expire_days,max_issue) values('monitor','5.0','any','lin32',30,10);
insert into demo_node(component,version,idtype,os,expire_days,max_issue) values('monitor','5.0','any','lin64',30,10);

insert into demo_float(component,version,idtype,os,server,port,count,expire_days,max_issue) values('monitor','5.0','ethernet','mac32','localhost','29750',10,30,10);
insert into demo_float(component,version,idtype,os,server,port,count,expire_days,max_issue) values('monitor','5.0','ethernet','mac64','localhost','29750',10,30,10);
insert into demo_float(component,version,idtype,os,server,port,count,expire_days,max_issue) values('monitor','5.0','ethernet','lin32','localhost','29750',10,30,10);
insert into demo_float(component,version,idtype,os,server,port,count,expire_days,max_issue) values('monitor','5.0','ethernet','lin64','localhost','29750',10,30,10);
insert into demo_float(component,version,idtype,os,server,port,count,expire_days,max_issue) values('monitor','5.0','ethernet','win32','localhost','29750',10,30,10);
insert into demo_float(component,version,idtype,os,server,port,count,expire_days,max_issue) values('monitor','5.0','ethernet','win64','localhost','29750',10,30,10);
