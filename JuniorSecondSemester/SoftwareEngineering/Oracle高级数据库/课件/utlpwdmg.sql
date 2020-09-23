Rem
Rem $Header: utlpwdmg.sql 02-aug-2006.08:18:05 asurpur Exp $
Rem
Rem utlpwdmg.sql
Rem
Rem Copyright (c) 2006, Oracle. All rights reserved.  
Rem
Rem    NAME
Rem      utlpwdmg.sql - script for Default Password Resource Limits
Rem
Rem    DESCRIPTION
Rem      This is a script for enabling the password management features
Rem      by setting the default password resource limits.
Rem
Rem    NOTES
Rem      This file contains a function for minimum checking of password
Rem      complexity. This is more of a sample function that the customer
Rem      can use to develop the function for actual complexity checks that the 
Rem      customer wants to make on the new password.
Rem
Rem    MODIFIED   (MM/DD/YY)
Rem    asurpur     05/30/06 - fix - 5246666 beef up password complexity check 
Rem    nireland    08/31/00 - Improve check for username=password. #1390553
Rem    nireland    06/28/00 - Fix null old password test. #1341892
Rem    asurpur     04/17/97 - Fix for bug479763
Rem    asurpur     12/12/96 - Changing the name of password_verify_function
Rem    asurpur     05/30/96 - New script for default password management
Rem    asurpur     05/30/96 - Created
Rem


-- This script sets the default password resource parameters
-- This script needs to be run to enable the password features.
-- However the default resource parameters can be changed based 
-- on the need.
-- A default password complexity function is also provided.
-- This function makes the minimum complexity checks like
-- the minimum length of the password, password not same as the
-- username, etc. The user may enhance this function according to
-- the need.
-- This function must be created in SYS schema.
-- connect sys/<password> as sysdba before running the script

CREATE OR REPLACE FUNCTION verify_function_11G
(username varchar2,
  password varchar2,
  old_password varchar2)
  RETURN boolean IS 
   n boolean;
   m integer;
   differ integer;
   isdigit boolean;
   ischar  boolean;
   ispunct boolean;
   db_name varchar2(40);
   digitarray varchar2(20);
   punctarray varchar2(25);
   chararray varchar2(52);
   i_char varchar2(10);
   simple_password varchar2(10);
   reverse_user varchar2(32);

BEGIN 
   digitarray:= '0123456789';
   chararray:= 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';

   -- Check for the minimum length of the password
   IF length(password) < 8 THEN
      raise_application_error(-20001, 'Password length less than 8');
   END IF;


   -- Check if the password is same as the username or username(1-100)
   IF NLS_LOWER(password) = NLS_LOWER(username) THEN
     raise_application_error(-20002, 'Password same as or similar to user');
   END IF;
   FOR i IN 1..100 LOOP
      i_char := to_char(i);
      if NLS_LOWER(username)|| i_char = NLS_LOWER(password) THEN
        raise_application_error(-20005, 'Password same as or similar to user name ');
      END IF;
    END LOOP;

   -- Check if the password is same as the username reversed
   
   FOR i in REVERSE 1..length(username) LOOP
     reverse_user := reverse_user || substr(username, i, 1);
   END LOOP;
   IF NLS_LOWER(password) = NLS_LOWER(reverse_user) THEN
     raise_application_error(-20003, 'Password same as username reversed');
   END IF;

   -- Check if the password is the same as server name and or servername(1-100)
   select name into db_name from sys.v$database;
   if NLS_LOWER(db_name) = NLS_LOWER(password) THEN
      raise_application_error(-20004, 'Password same as or similar to server name');
   END IF;
   FOR i IN 1..100 LOOP
      i_char := to_char(i);
      if NLS_LOWER(db_name)|| i_char = NLS_LOWER(password) THEN
        raise_application_error(-20005, 'Password same as or similar to server name ');
      END IF;
    END LOOP;

   -- Check if the password is too simple. A dictionary of words may be
   -- maintained and a check may be made so as not to allow the words
   -- that are too simple for the password.
   IF NLS_LOWER(password) IN ('welcome1', 'database1', 'account1', 'user1234', 'password1', 'oracle123', 'computer1', 'abcdefg1', 'change_on_install') THEN
      raise_application_error(-20006, 'Password too simple');
   END IF;

   -- Check if the password is the same as oracle (1-100)
    simple_password := 'oracle';
    FOR i IN 1..100 LOOP
      i_char := to_char(i);
      if simple_password || i_char = NLS_LOWER(password) THEN
        raise_application_error(-20007, 'Password too simple ');
      END IF;
    END LOOP;

   -- Check if the password contains at least one letter, one digit 
   -- 1. Check for the digit
   isdigit:=FALSE;
   m := length(password);
   FOR i IN 1..10 LOOP 
      FOR j IN 1..m LOOP 
         IF substr(password,j,1) = substr(digitarray,i,1) THEN
            isdigit:=TRUE;
             GOTO findchar;
         END IF;
      END LOOP;
   END LOOP;

   IF isdigit = FALSE THEN
      raise_application_error(-20008, 'Password must contain at least one digit, one character');
   END IF;
   -- 2. Check for the character
   <<findchar>>
   ischar:=FALSE;
   FOR i IN 1..length(chararray) LOOP 
      FOR j IN 1..m LOOP 
         IF substr(password,j,1) = substr(chararray,i,1) THEN
            ischar:=TRUE;
             GOTO endsearch;
         END IF;
      END LOOP;
   END LOOP;
   IF ischar = FALSE THEN
      raise_application_error(-20009, 'Password must contain at least one \
              digit, and one character');
   END IF;


   <<endsearch>>
   -- Check if the password differs from the previous password by at least
   -- 3 letters
   IF old_password IS NOT NULL THEN
     differ := length(old_password) - length(password);

     differ := abs(differ);
     IF differ < 3 THEN
       IF length(password) < length(old_password) THEN
         m := length(password);
       ELSE
         m := length(old_password);
       END IF;

       FOR i IN 1..m LOOP
         IF substr(password,i,1) != substr(old_password,i,1) THEN
           differ := differ + 1;
         END IF;
       END LOOP;

       IF differ < 3 THEN
         raise_application_error(-20011, 'Password should differ from the \
            old password by at least 3 characters');
       END IF;
     END IF;
   END IF;
   -- Everything is fine; return TRUE ;   
   RETURN(TRUE);
END;
/

-- This script alters the default parameters for Password Management
-- This means that all the users on the system have Password Management
-- enabled and set to the following values unless another profile is 
-- created with parameter values set to different value or UNLIMITED 
-- is created and assigned to the user.

ALTER PROFILE DEFAULT LIMIT
PASSWORD_LIFE_TIME 180
PASSWORD_GRACE_TIME 7
PASSWORD_REUSE_TIME UNLIMITED
PASSWORD_REUSE_MAX UNLIMITED
FAILED_LOGIN_ATTEMPTS 10
PASSWORD_LOCK_TIME 1
PASSWORD_VERIFY_FUNCTION verify_function_11G;



-- Below is the older version of the script

-- This script sets the default password resource parameters
-- This script needs to be run to enable the password features.
-- However the default resource parameters can be changed based 
-- on the need.
-- A default password complexity function is also provided.
-- This function makes the minimum complexity checks like
-- the minimum length of the password, password not same as the
-- username, etc. The user may enhance this function according to
-- the need.
-- This function must be created in SYS schema.
-- connect sys/<password> as sysdba before running the script

CREATE OR REPLACE FUNCTION verify_function
(username varchar2,
  password varchar2,
  old_password varchar2)
  RETURN boolean IS 
   n boolean;
   m integer;
   differ integer;
   isdigit boolean;
   ischar  boolean;
   ispunct boolean;
   digitarray varchar2(20);
   punctarray varchar2(25);
   chararray varchar2(52);

BEGIN 
   digitarray:= '0123456789';
   chararray:= 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
   punctarray:='!"#$%&()``*+,-/:;<=>?_';

   -- Check if the password is same as the username
   IF NLS_LOWER(password) = NLS_LOWER(username) THEN
     raise_application_error(-20001, 'Password same as or similar to user');
   END IF;

   -- Check for the minimum length of the password
   IF length(password) < 4 THEN
      raise_application_error(-20002, 'Password length less than 4');
   END IF;

   -- Check if the password is too simple. A dictionary of words may be
   -- maintained and a check may be made so as not to allow the words
   -- that are too simple for the password.
   IF NLS_LOWER(password) IN ('welcome', 'database', 'account', 'user', 'password', 'oracle', 'computer', 'abcd') THEN
      raise_application_error(-20002, 'Password too simple');
   END IF;

   -- Check if the password contains at least one letter, one digit and one
   -- punctuation mark.
   -- 1. Check for the digit
   isdigit:=FALSE;
   m := length(password);
   FOR i IN 1..10 LOOP 
      FOR j IN 1..m LOOP 
         IF substr(password,j,1) = substr(digitarray,i,1) THEN
            isdigit:=TRUE;
             GOTO findchar;
         END IF;
      END LOOP;
   END LOOP;
   IF isdigit = FALSE THEN
      raise_application_error(-20003, 'Password should contain at least one digit, one character and one punctuation');
   END IF;
   -- 2. Check for the character
   <<findchar>>
   ischar:=FALSE;
   FOR i IN 1..length(chararray) LOOP 
      FOR j IN 1..m LOOP 
         IF substr(password,j,1) = substr(chararray,i,1) THEN
            ischar:=TRUE;
             GOTO findpunct;
         END IF;
      END LOOP;
   END LOOP;
   IF ischar = FALSE THEN
      raise_application_error(-20003, 'Password should contain at least one \
              digit, one character and one punctuation');
   END IF;
   -- 3. Check for the punctuation
   <<findpunct>>
   ispunct:=FALSE;
   FOR i IN 1..length(punctarray) LOOP 
      FOR j IN 1..m LOOP 
         IF substr(password,j,1) = substr(punctarray,i,1) THEN
            ispunct:=TRUE;
             GOTO endsearch;
         END IF;
      END LOOP;
   END LOOP;
   IF ispunct = FALSE THEN
      raise_application_error(-20003, 'Password should contain at least one \
              digit, one character and one punctuation');
   END IF;

   <<endsearch>>
   -- Check if the password differs from the previous password by at least
   -- 3 letters
   IF old_password IS NOT NULL THEN
     differ := length(old_password) - length(password);

     IF abs(differ) < 3 THEN
       IF length(password) < length(old_password) THEN
         m := length(password);
       ELSE
         m := length(old_password);
       END IF;

       differ := abs(differ);
       FOR i IN 1..m LOOP
         IF substr(password,i,1) != substr(old_password,i,1) THEN
           differ := differ + 1;
         END IF;
       END LOOP;

       IF differ < 3 THEN
         raise_application_error(-20004, 'Password should differ by at \
         least 3 characters');
       END IF;
     END IF;
   END IF;
   -- Everything is fine; return TRUE ;   
   RETURN(TRUE);
END;
/

-- This script alters the default parameters for Password Management
-- This means that all the users on the system have Password Management
-- enabled and set to the following values unless another profile is 
-- created with parameter values set to different value or UNLIMITED 
-- is created and assigned to the user.

-- Enable this if you want older version of the Password Profile parameters
-- ALTER PROFILE DEFAULT LIMIT
-- PASSWORD_LIFE_TIME 60
-- PASSWORD_GRACE_TIME 10
-- PASSWORD_REUSE_TIME 1800
-- PASSWORD_REUSE_MAX UNLIMITED
-- FAILED_LOGIN_ATTEMPTS 3
-- PASSWORD_LOCK_TIME 1/1440
-- PASSWORD_VERIFY_FUNCTION verify_function;
