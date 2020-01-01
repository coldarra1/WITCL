--删除各种约束及表
PROMPT
PROMPT 删除HR模式下已有数据库对象......

ALTER TABLE departments DROP CONSTRAINT dept_mgr_fk;
ALTER TABLE employees DROP CONSTRAINT emp_mgr_fk;

DROP TABLE sal_grades;
DROP TABLE job_history;
DROP TABLE employees;
DROP TABLE jobs;
DROP TABLE departments;
DROP TABLE locations;
DROP TABLE countries;
DROP TABLE regions;

DROP SEQUENCE employees_seq;
DROP SEQUENCE departments_seq;
DROP SEQUENCE locations_seq;

--创建REGIONS表
PROMPT
PROMPT 创建REGIONS表......

CREATE TABLE regions
( region_id NUMBER PRIMARY KEY, 
  region_name VARCHAR2(25)
)
TABLESPACE USERS;

--创建COUNTRIES表
PROMPT
PROMPT 创建COUNTRIES表......

CREATE TABLE countries
( country_id CHAR(2) PRIMARY KEY, 
  country_name VARCHAR2(40), 
  region_id NUMBER REFERENCES regions(region_id)
)
  ORGANIZATION INDEX
  TABLESPACE USERS;


--创建LOCATIONS表
PROMPT
PROMPT 创建LOCATIONS表......

CREATE TABLE locations
( location_id NUMBER(4) PRIMARY KEY, 
  street_address VARCHAR2(40), 
  postal_code VARCHAR2(12), 
  city VARCHAR2(30) NOT NULL, 
  state_province VARCHAR2(25), 
  country_id CHAR(2)  REFERENCES countries(country_id)
)
 TABLESPACE USERS;


--创建DEPARTMENTS表
PROMPT
PROMPT 创建DEPARTMENTS表......

CREATE TABLE departments
( department_id NUMBER(4) PRIMARY KEY, 
  department_name VARCHAR2(30) NOT NULL, 
  manager_id NUMBER(6) , 
  location_id NUMBER(4) REFERENCES locations (location_id)
)
 TABLESPACE USERS;


--创建JOBS表
PROMPT
PROMPT 创建JOBS表......

CREATE TABLE jobs
( job_id VARCHAR2(10) PRIMARY KEY, 
  job_title VARCHAR2(35) NOT NULL, 
  min_salary NUMBER(6), 
  max_salary NUMBER(6)
)
 TABLESPACE USERS;

--创建EMPLOYEES表
PROMPT
PROMPT 创建EMPLOYEES表......

CREATE TABLE employees
( employee_id NUMBER(6) PRIMARY KEY, 
  first_name VARCHAR2(20), 
  last_name VARCHAR2(25) NOT NULL, 
  email VARCHAR2(25) NOT NULL UNIQUE, 
  phone_number VARCHAR2(20), 
  hire_date DATE NOT NULL, 
  job_id VARCHAR2(10) NOT NULL REFERENCES jobs (job_id), 
  salary NUMBER(8,2) CHECK (salary > 0),
  commission_pct NUMBER(2,2), 
  manager_id NUMBER(6), 
  department_id NUMBER(4) REFERENCES departments(department_id)
) 
 TABLESPACE USERS;

--创建JOB_HISTORY表
PROMPT
PROMPT 创建JOB_HISTORY表......

CREATE TABLE job_history
( employee_id NUMBER(6) NOT NULL REFERENCES employees(employee_id), 
  start_date DATE NOT NULL, 
  end_date DATE NOT NULL, 
  job_id VARCHAR2(10) NOT NULL REFERENCES jobs(job_id), 
  department_id NUMBER(4) REFERENCES departments(department_id),
  CONSTRAINT jhist_date_interval CHECK (end_date > start_date),
  CONSTRAINT jhist_emp_id_st_date_pk PRIMARY KEY (employee_id, start_date)
) 
 TABLESPACE USERS;

--创建SAL_GRADES表
PROMPT
PROMPT 创建SAL_GRADES表......

CREATE TABLE sal_grades
(grade  NUMBER PRIMARY KEY,
min_salary  NUMBER(8,2),
max_salary  NUMBER(8,2)
)
TABLESPACE USERS;

--创建MANAGER表
PROMPT
PROMPT 创建MANAGER表......

CREATE TABLE managers(
manager_id NUMBER(2)PRIMARY KEY,
manager_name CHAR(20),
password  VARCHAR2(20) NOT NULL
)
TABLESPACE USERS


--为departments表的manager_id列添加外键约束
PROMPT
PROMPT 添加外键约束......

ALTER TABLE departments ADD CONSTRAINT dept_mgr_fk FOREIGN KEY(manager_id) references employees(employee_id) DISABLE;
--为employees表的manager_id列添加外键约束
ALTER TABLE employees ADD CONSTRAINT emp_mgr_fk FOREIGN KEY(manager_id) references employees(employee_id) DISABLE;


/*
为了提高数据的查询效率，需要在适当表的适当列上创建索引，并将索引存储在INDX表空间中。

（1）在employees 表的department_id列上创建一个名为“EMP_DEPARTMENT_INDX”的平衡树索引。
（2）在employees 表的job_id列上创建一个名为“EMP_JOB_INDX”的平衡树索引。
（3）在employees 表的manager_id列上创建一个名为“EMP_MANAGER_INDX”的平衡树索引。
（4）在employees 表的last_name, first_name列上创建一个名为“EMP_NAME_INDX”的复合索引。
（5）在departments 表的location_id列上创建一个名为“DEPT_LOCATION_INDX”的平衡树索引。
（6）在job_history 表的job_id列上创建一个名为“JHIST_JOB_INDX”的平衡树索引。
（7）在job_history表的employee_id列上创建一个名为“JHIST_EMP_INDX”的平衡树索引。
（8）在job_history表的department_id列上创建一个名为“JHIST_DEPT_INDX”的平衡树索引。
（9）在locations表的city列上创建一个名为“LOC_CITY_INDX”的平衡树索引。
（10）在locations表的state_province列上创建一个名为“LOC_STATE_PROVINCE_INDX”的平衡树索引。
（11）在locations表的country_id列上创建一个名为“LOC_COUNTRY_INDX”的平衡树索引。
*/

PROMPT
PROMPT 创建索引......

CREATE INDEX emp_department_INDX ON employees (department_id) TABLESPACE indx;
CREATE INDEX emp_job_INDX ON employees(job_id) TABLESPACE indx;
CREATE INDEX emp_manager_INDX ON employees (manager_id) TABLESPACE indx;
CREATE INDEX emp_name_INDX ON employees (last_name, first_name) TABLESPACE indx;
CREATE INDEX dept_location_INDX ON departments (location_id) TABLESPACE indx;
CREATE INDEX jhist_job_INDX ON job_history (job_id) TABLESPACE indx;
CREATE INDEX jhist_emp_INDX ON job_history (employee_id) TABLESPACE indx;
CREATE INDEX jhist_dept_INDX ON job_history (department_id) TABLESPACE indx;
CREATE INDEX loc_city_INDX ON locations (city) TABLESPACE indx;
CREATE INDEX loc_state_province_INDX ON locations (state_province) TABLESPACE indx;
CREATE INDEX loc_country_INDX ON locations (country_id) TABLESPACE indx;



PROMPT
PROMPT 创建视图......

--创建一个名为“EMP_DETAILS_VIEW”的视图，包含各个员工的员工号、职位、部门号、国家和位置信息。
CREATE OR REPLACE VIEW emp_details_view
(employee_id,job_id,manager_id,department_id,location_id,country_id,first_name,last_name,salary,commission_pct,
department_name,job_title,city,state_province,country_name,region_name)
AS 
SELECT e.employee_id,e.job_id,e.manager_id,e.department_id,d.location_id,l.country_id,e.first_name,e.last_name,
e.salary,e.commission_pct,d.department_name,j.job_title,l.city,l.state_province,c.country_name,r.region_name
FROM employees e,departments d,jobs j,locations l,countries c,regions r
WHERE e.department_id = d.department_id AND d.location_id = l.location_id AND l.country_id = c.country_id
AND c.region_id = r.region_id AND j.job_id = e.job_id 
WITH READ ONLY;

--创建一个名为“DEPT_STAT_VIEW”的视图，包含部门号、部门人数、部门平均工资、部门最高工资、部门最低工资以及部门工资总和。
CREATE OR REPLACE VIEW dept_stat_view
AS
SELECT department_id,count(*) num,avg(salary) avgsal,max(salary) maxsal,min(salary) minsal,sum(salary) totalsal
FROM employees GROUP BY department_id;



PROMPT
PROMPT 创建序列......

--创建一个名为“EMPLOYEES_SEQ”的序列，用于产生员工编号，起始值为100，步长为1，不缓存，不循环。
CREATE SEQUENCE employees_seq
START WITH 100
INCREMENT BY 1
NOCACHE
NOCYCLE;

--创建一个名为“DEPARTMENTS_SEQ”的序列，用于产生部门编号，起始值为10，步长为10，最大值为9990，不缓存，不循环。

CREATE SEQUENCE departments_seq
START WITH 10
INCREMENT BY 10
MAXVALUE 9990
NOCACHE
NOCYCLE;

--创建一个名为“LOCATIONS_SEQ”的序列，用于产生位置编号，起始值为1000，步长为100，最大值为9990，不缓存，不循环。
CREATE SEQUENCE locations_seq
START WITH 1000
INCREMENT BY 100
MAXVALUE 9900
NOCACHE
NOCYCLE;

