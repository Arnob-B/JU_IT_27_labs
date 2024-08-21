# What is it about
here you will find all the solutions to the dbms assignments before I submit them to classroom

# question 5 of assignment 2
'''

declare
    jobs varchar(20) ; 
CURSOR C_EMP IS
    SELECT * FROM EMP WHERE JOB = JOBS;
    ROWREC C_EMP%ROWTYPE; 

BEGIN 
    JOBS :='CLERK';
 DBMS_OUTPUT.PUT_LINE('EMPNO' || ' '||'ENAME' || ' '||'JOB' || ' '||'MGR '|| ' '||'HIREDATE '|| ' '||'SAL' || ' '||'COMM' || ' '||'DEPTNO '|| ' '||'PHONENO '|| ' '||'ADDRESS' );

OPEN C_EMP;
LOOP 
    FETCH C_EMP INTO ROWREC;
    EXIT WHEN C_EMP%NOTFOUND;
    DBMS_OUTPUT.PUT_LINE(ROWREC.EMPNO || ' '||ROWREC.ENAME || ' '||ROWREC.JOB || ' '||ROWREC.MGR || ' '||ROWREC.HIREDATE || ' '||ROWREC.SAL || ' '||ROWREC.COMM || ' '||ROWREC.DEPTNO || ' '||ROWREC.PHONENO || ' '||ROWREC.ADDRESS );
	END LOOP;
CLOSE C_EMP;
END;





'''
