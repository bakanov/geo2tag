CREATE SEQUENCE users_seq INCREMENT 1 MINVALUE 1 START 1 CACHE 1;

CREATE TABLE users (
  id NUMERIC(9,0) NOT NULL DEFAULT nextval('users_seq'),
  login VARCHAR(50) NOT NULL,
  password VARCHAR(50) NOT NULL,
  token VARCHAR(65) UNIQUE NOT NULL,
  constraint users_pkey primary key (id)
);

CREATE SEQUENCE tags_seq INCREMENT 1 MINVALUE 1 START 1 CACHE 1;

CREATE TABLE tag (
  id NUMERIC(9,0) NOT NULL DEFAULT nextval('tags_seq'),
  time TIMESTAMP NOT NULL DEFAULT (current_timestamp),
  latitude float NOT NULL,
  longitude float NOT NULL,
  label VARCHAR(1024) NOT NULL,
  description VARCHAR(2048) NOT NULL, 
  url VARCHAR(2048) DEFAULT NULL, 
  user_id NUMERIC(9,0) NOT NULL DEFAULT 1,
  constraint tag_pkey primary key (id),
  constraint fk_user foreign key (user_id) references users(id)
                                                      on delete cascade
);

CREATE SEQUENCE channels_seq INCREMENT 1 MINVALUE 1 START 1 CACHE 1;

CREATE TABLE channel (
  id NUMERIC(9,0) NOT NULL DEFAULT nextval('channels_seq'),
  name VARCHAR(300) NOT NULL,
  description VARCHAR(2048) NOT NULL, 
  url VARCHAR(2048) DEFAULT NULL,
  constraint channel_pkey primary key (id)
);

CREATE TABLE tags (
  channel_id NUMERIC(9,0) NOT NULL,
  tag_id NUMERIC(9,0) NOT NULL,
  constraint fk_tags  foreign key (tag_id) references tag(id)
                                                       on delete cascade,
  constraint fk_channels foreign key (channel_id) references channel(id)
                                                       on delete cascade
);

CREATE TABLE subscribe (
  channel_id NUMERIC(9,0) NOT NULL,
  user_id NUMERIC(9,0) NOT NULL,
  constraint fk_tags  foreign key (user_id) references users(id)
                                                       on delete cascade,
  constraint fk_channels foreign key (channel_id) references channel(id)
                                                       on delete cascade
);

CREATE SEQUENCE timeSlots_seq INCREMENT 1 MINVALUE 1 START 1 CACHE 1;

CREATE TABLE timeSlot (
  id NUMERIC(9,0) NOT NULL DEFAULT nextval('timeSlots_seq'),
  slot BIGINT NOT NULL,  
  constraint timeSlot_pkey primary key (id)  
);

CREATE TABLE channelTimeSlot (
  channel_id NUMERIC(9,0) NOT NULL,
  timeSlot_id NUMERIC(9,0) NOT NULL,
  constraint fk_timeSlot foreign key (timeSlot_id) references timeSlot(id)
                                                       on delete cascade,
  constraint fk_channels foreign key (channel_id) references channel(id)
                                                       on delete cascade
);

CREATE TABLE tagTimeSlot (
  tag_id NUMERIC(9,0) NOT NULL,
  timeSlot_id NUMERIC(9,0) NOT NULL,
  constraint fk_timeSlot foreign key (timeSlot_id) references timeSlot(id)
                                                       on delete cascade,
  constraint fk_tags foreign key (tag_id) references tag(id)
                                                       on delete cascade
);

CREATE SEQUENCE actions_seq INCREMENT 1 MINVALUE 1 START 1 CACHE 1;

CREATE TABLE action (
id NUMERIC(9,0) NOT NULL DEFAULT nextval('actions_seq'),
mask SERIAL NOT NULL,
name VARCHAR(300) NOT NULL,
CONSTRAINT id_pk PRIMARY KEY(id),
unique (mask, name)
);

CREATE SEQUENCE channel_actions_seq INCREMENT 1 MINVALUE 1 START 1 CACHE 1;

CREATE TABLE channel_action (
id NUMERIC(9,0) NOT NULL DEFAULT nextval('channel_actions_seq'),
user_id NUMERIC(9,0) NOT NULL,
channel_id NUMERIC(9,0) NOT NULL,
action SERIAL,
CONSTRAINT channel_action_pkey primary key (id),
CONSTRAINT user_id_channel_action_fk foreign key (user_id) references users(id) on delete cascade,
CONSTRAINT channel_id_fk foreign key (channel_id) references channel(id) on delete cascade,
unique (user_id, channel_id, action)
);

CREATE SEQUENCE tag_actions_seq INCREMENT 1 MINVALUE 1 START 1 CACHE 1;

CREATE TABLE tag_action (
id NUMERIC(9,0) NOT NULL DEFAULT nextval('tag_actions_seq'),
user_id NUMERIC(9,0) NOT NULL,
tag_id NUMERIC(9,0) NOT NULL,
action SERIAL,
CONSTRAINT tag_action_pkey primary key (id),
CONSTRAINT user_id_fk foreign key (user_id) references users(id) on delete cascade,
CONSTRAINT tag_id_fk foreign key (tag_id) references tag(id) on delete cascade,
unique (user_id, tag_id, action)
);

INSERT into channel_action (user_id, channel_id, action) values (5, 3, 3);
INSERT into channel_action (user_id, channel_id, action) values (2, 5, 5);
INSERT into channel_action (user_id, channel_id, action) values (3, 4, 3);

INSERT into action (mask, name) values (1,  'subscribe');
INSERT into action (mask, name) values (2,  'unsubscribe');
INSERT into action (mask, name) values (4,  'write');
INSERT into action (mask, name) values (8,  'read');
INSERT into action (mask, name) values (16, 'create');
INSERT into action (mask, name) values (32, 'remove');

INSERT into tag_action (user_id, tag_id, action) values (1, 1, 3);
INSERT into tag_action (user_id, tag_id, action) values (2, 1, 3);



INSERT into channel (name, description, url) values ('Tourist information', 'This is free read-only tourist information channel. You can get information about buildings, sights around your location', '');
INSERT into channel (name, description, url) values ('Public announcements', 'This is free read-only channel with public announcements from the city of your current location', '');
INSERT into channel (name, description, url) values ('Fuel prices', 'This is free channel where you can post/read the fuel prices around your current location.', '');
INSERT into channel (name, description, url) values ('Sales', 'This is free channel where you can post/read sales advertisements', '');
INSERT into channel (name, description, url) values ('My channel', 'This is free channel where you and your friends can post/read your tags', '');

INSERT into users (login, password, token) values ('Paul',   'test', 'PPPPPPPPPP');
INSERT into users (login, password, token) values ('Kirill', 'test', 'KKKKKKKKKK');
INSERT into users (login, password, token) values ('Mark',   'test', 'MMMMMMMMMM');
INSERT into users (login, password, token) values ('Yevgeni', 'test', 'YYYYYYYYYY');

INSERT into tag(latitude, longitude, label, description, user_id, url) values(60.166504, 24.841204, 'A', 'Accident at road 51. Time: 15:45, January 2, 2010.', 1, 'http://dps.sd.gov/licensing/driver_licensing/images/Image24.gif');
INSERT into tag(latitude, longitude, label, description, user_id, url) values(60.163216, 24.859314, 'B', 'Shell 95: 1.299 e', 2, 'http://www.unf.edu/groups/volctr/images/question-mark.jpg');
INSERT into tag(latitude, longitude, label, description, user_id, url) values(60.166264, 24.859915, 'C', 'Neste Oil diesel: .0989 e', 1, 'http://www.unf.edu/groups/volctr/images/question-mark.jpg');
INSERT into tag(latitude, longitude, label, description, user_id, url) values(60.163216, 24.859915, 'D', 'Neste 95: 1.294 e', 3, 'http://www.unf.edu/groups/volctr/images/question-mark.jpg');
INSERT into tag(latitude, longitude, label, description, user_id, url) values(60.162159, 24.739065, 'E', 'CityMarket Iso Omena: Children overalls 50% off', 1, 'http://www.k-citymarket.fi/img/citymarketLogo.gif');
INSERT into tag(latitude, longitude, label, description, user_id, url) values(60.167433, 24.733486, 'F', 'Prisma Olari: LEGO 20% off', 2, 'http://mw2.google.com/mw-panoramio/photos/thumbnail/5131282.jpg');
INSERT into tag(latitude, longitude, label, description, user_id, url) values(60.173362, 24.829166, 'G', 'Outdoor party place on February 20, 2010', 4, 'http://www.unf.edu/groups/volctr/images/question-mark.jpg');
INSERT into tag(latitude, longitude, label, description, user_id, url) values(60.178308, 24.848585, 'H', 'Espoo. Cheap hotel.', 2, 'http://mw2.google.com/mw-panoramio/photos/small/8267319.jpg');

INSERT into tags (channel_id, tag_id) values (2, 1);
INSERT into tags (channel_id, tag_id) values (3, 2);
INSERT into tags (channel_id, tag_id) values (3, 3);
INSERT into tags (channel_id, tag_id) values (3, 4);
INSERT into tags (channel_id, tag_id) values (4, 5);
INSERT into tags (channel_id, tag_id) values (4, 6);
INSERT into tags (channel_id, tag_id) values (5, 7);
INSERT into tags (channel_id, tag_id) values (1, 8);

INSERT into timeSlot (slot) values (259200);
INSERT into timeSlot (slot) values (10080);
INSERT into timeSlot (slot) values (1440);

INSERT into channelTimeSlot (channel_id, timeSlot_id) values (1, 1);
INSERT into channelTimeSlot (channel_id, timeSlot_id) values (2, 2);
INSERT into channelTimeSlot (channel_id, timeSlot_id) values (3, 3);
INSERT into channelTimeSlot (channel_id, timeSlot_id) values (4, 3);
INSERT into channelTimeSlot (channel_id, timeSlot_id) values (5, 2);

INSERT into tagTimeSlot (tag_id, timeSlot_id) values (5, 2);
INSERT into tagTimeSlot (tag_id, timeSlot_id) values (6, 1);
