#include <stdio.h>
#include <sqlite3.h> 
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
   sqlite3 *db;
   // char* errmsg;  add error message when there is nothing in the query with the info provided???
   int rc;
   sqlite3_stmt *stmt;
   char* sql;

   

   //OPENS DATABASE
   rc = sqlite3_open("test.db", &db);

   if( rc != SQLITE_OK)
     {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
     }
   else
     {
      fprintf(stderr, "Opened database successfully\n");  
     }

   std::cout<<"\n";

   std::cout << "Sections:" << endl;

   sql = "SELECT * FROM Section";

   rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

  if (rc != SQLITE_OK)
    {
   fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
   sqlite3_finalize(stmt);
    }
  
     rc = sqlite3_step(stmt);

    if (rc != SQLITE_ROW && rc != SQLITE_DONE)
      {
      fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);

      }

    while(rc == SQLITE_ROW)
      {
        printf("%s ", sqlite3_column_text(stmt, 0));
        printf("%s ", sqlite3_column_text(stmt, 1));
        printf("%s ", sqlite3_column_text(stmt, 2));
        printf("%s ", sqlite3_column_text(stmt, 3));
        printf("%s ", sqlite3_column_text(stmt, 4));
        printf("%s ", sqlite3_column_text(stmt, 5));
        printf("%s ", sqlite3_column_text(stmt, 6));
        printf("%s ", sqlite3_column_text(stmt, 7));
        printf("%s\n", sqlite3_column_text(stmt, 8));

        rc = sqlite3_step(stmt);

      }
    sqlite3_finalize(stmt);

    std::cout<<"\n";
    
   std::cout << "Courses:" << endl;

   sql = "SELECT * FROM Course";

   rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

  if (rc != SQLITE_OK)
    {
   fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
   sqlite3_finalize(stmt);
    }

     rc = sqlite3_step(stmt);

    if (rc != SQLITE_ROW && rc != SQLITE_DONE)
      {
      fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);

      }

    while(rc == SQLITE_ROW)
      {
        printf("%s ", sqlite3_column_text(stmt, 0));
        printf("%s ", sqlite3_column_text(stmt, 1));
        printf("%s\n", sqlite3_column_text(stmt, 2));

        rc = sqlite3_step(stmt);

      }
    sqlite3_finalize(stmt);

    std::cout<<"\n";


   
    std::string ans;
   std::cout<< "Would you like to see a list of courses in a specific term? (yes or no): ";
   std::cin >> ans;

   std::cout<<"\n";

   if(ans == "yes")
     {
   //SELECT QUERY FOR ALL COURSES  in term by term spring or fall???
   
   std::string term;
   std:: cout << "Enter Term (Fall or Spring): ";
   std::cin >> term;
    std::cout<<"\n";

    sql = "SELECT TITLE FROM Section WHERE Semester = ?";

   rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

  if (rc != SQLITE_OK)
    {
   fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
   sqlite3_finalize(stmt);
    }

  rc = sqlite3_bind_text(stmt, 1, term.c_str(), -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK)
      {
      fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
       sqlite3_finalize(stmt);
      }

     rc = sqlite3_step(stmt);

    if (rc != SQLITE_ROW && rc != SQLITE_DONE)
      {
      fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);

      }

    while(rc == SQLITE_ROW)
      {
        printf("%s\n", sqlite3_column_text(stmt, 0));

        rc = sqlite3_step(stmt);

      }
    sqlite3_finalize(stmt);
    std::cout<<"\n";

     }

   std::string ans2;
    std::cout<< "Would you like to search for the courses in a certain department? (yes or no): ";
    std::cin >> ans2;
    std::cout<<"\n";

   if(ans2 == "yes")
     {
    //READS DEPARTMENT AND PRINTS ALL THE COURSES
    std::string name;
    std:: cout << "Enter Department(MATH,CMSC,etc.): ";
    std::cin >> name;
    std::cout<<"\n";
    
     sql = "SELECT TITLE FROM Section WHERE DEPARTMENT = ?";

  
  
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK)
      {
      fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
      }

    
    rc = sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);    
    if (rc != SQLITE_OK)
      {                 
      fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
       sqlite3_finalize(stmt);
      }


    rc = sqlite3_step(stmt);

    if (rc != SQLITE_ROW && rc != SQLITE_DONE)
      {
      fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
       
      }
    
    while(rc == SQLITE_ROW)
      {  
        printf("%s\n", sqlite3_column_text(stmt, 0));
	
	rc = sqlite3_step(stmt);
      }
    sqlite3_finalize(stmt);
    std::cout<<"\n";

     }

   std::string ans3;
   std::cout<< "Would you like to search for the courses taught by a specific professor? (yes or no): ";
   std::cin >> ans3;
   std::cout<<"\n";

   if(ans3 == "yes")
     {

    // Reads in professor and prints his courses
    std::string prof;
    std:: cout << "Enter Professor's last name(Hill,Blaheta,etc.): ";
    std::cin >> prof;
    std::cout<<"\n";

    //Select the title from section table where pid = professor with that pid 

    char* sql = "SELECT TITLE FROM Section INNER JOIN Professor ON Section.PID = Professor.PID WHERE Professor.PNAME = ?";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK)
      {
      fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
      }


    rc = sqlite3_bind_text(stmt, 1, prof.c_str(), -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK)
      {
      fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
       sqlite3_finalize(stmt);
      }
    
     rc = sqlite3_step(stmt);

    if (rc != SQLITE_ROW && rc != SQLITE_DONE)
      {
      fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);

      }

    while(rc == SQLITE_ROW)
      {
        printf("%s\n", sqlite3_column_text(stmt, 0));

        rc = sqlite3_step(stmt);
      }

    sqlite3_finalize(stmt);
    std::cout<<"\n";

     }
    
   std::string ans4;
   std::cout<< "Would you like to add a course? (yes or no): ";
   std::cin >> ans4;
   std::cout<<"\n";

   if(ans4 == "yes")
     {

    // Inserts into Course table
    std::string title;
    std::cout << "Course Title(ex. Calculus): ";
    std::cin >> title;
    std::cout<<"\n"; 
    std::string depart;
    std::cout << "Course Department(ex. MATH): ";
    std::cin >> depart;
    std::cout<<"\n";
    std::string cnum;
    std::cout << "Course Number(ex. 162): ";
    std::cin >> cnum;
    std::cout<<"\n";
    
    
    char* sql = "INSERT INTO Course (TITLE, DEPARTMENT, CNUM) VALUES ( ?1, ?2, ?3); ";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK)
      {
      fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
      }

    rc = sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_TRANSIENT);

    if (rc != SQLITE_OK)
      {
       fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
       sqlite3_finalize(stmt);
      }

    rc = sqlite3_bind_text(stmt, 2, depart.c_str(), -1, SQLITE_TRANSIENT);

    if (rc != SQLITE_OK)
      {
       fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
       sqlite3_finalize(stmt);
      }

    rc = sqlite3_bind_text(stmt, 3, cnum.c_str(), -1, SQLITE_TRANSIENT);

    if (rc != SQLITE_OK)
      {
       fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
       sqlite3_finalize(stmt);
      }


    rc = sqlite3_step(stmt);

    if (rc != SQLITE_ROW && rc != SQLITE_DONE)
      {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);

      }
    else
      {
        fprintf(stdout, "Operation done successfully\n");
        sqlite3_finalize(stmt);
      }

    std::cout << "\n";
    std::cout << "Courses:" << endl;

   sql = "SELECT * FROM Course";

   rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

  if (rc != SQLITE_OK)
    {
   fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
   sqlite3_finalize(stmt);
    }

     rc = sqlite3_step(stmt);

    if (rc != SQLITE_ROW && rc != SQLITE_DONE)
      {
      fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);

      }

    while(rc == SQLITE_ROW)
      {
        printf("%s ", sqlite3_column_text(stmt, 0));
        printf("%s ", sqlite3_column_text(stmt, 1));
        printf("%s\n", sqlite3_column_text(stmt, 2));

        rc = sqlite3_step(stmt);

      }
    sqlite3_finalize(stmt);

    std::cout<<"\n";



     }

   std::string ans5;
   std::cout<< "Would you like to update a section's capacity? (yes or no): ";
   std::cin >> ans5;
   std::cout<<"\n";

   if(ans5 == "yes")
     {

       int capacity;
       
   std::string crn;
   std::cout<<"Enter the CRN of the section's capacity you'd like to update(ex.12389421): ";
   std::cin >> crn;
   std::cout<<"\n";
   
   std::cout<<"Enter the new capacity(ex. 2): ";
   std:: cin >> capacity;
   std::cout<<"\n";

     sql = "UPDATE Section SET CAPACITY = ?1 where CRN =?2;";

   rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

  if (rc != SQLITE_OK)
    {
   fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
   sqlite3_finalize(stmt);
    }

    rc = sqlite3_bind_int(stmt, 1, capacity);
    if (rc != SQLITE_OK)
      {
      fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
       sqlite3_finalize(stmt);
      }
    rc = sqlite3_bind_text(stmt, 2, crn.c_str(), -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK)
      {
      fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
       sqlite3_finalize(stmt);
      }

     rc = sqlite3_step(stmt);

    if (rc != SQLITE_ROW && rc != SQLITE_DONE)
      {
      fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);

      }

 else
      {
        fprintf(stdout, "Operation done successfully\n");
        sqlite3_finalize(stmt);
      }

    std::cout << "\n";
     std::cout << "Sections:" << endl;

   sql = "SELECT * FROM Section";

   rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

  if (rc != SQLITE_OK)
    {
   fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
   sqlite3_finalize(stmt);
    }

     rc = sqlite3_step(stmt);

    if (rc != SQLITE_ROW && rc != SQLITE_DONE)
      {
      fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);

      }

    while(rc == SQLITE_ROW)
      {
        printf("%s ", sqlite3_column_text(stmt, 0));
        printf("%s ", sqlite3_column_text(stmt, 1));
        printf("%s ", sqlite3_column_text(stmt, 2));
        printf("%s ", sqlite3_column_text(stmt, 3));
        printf("%s ", sqlite3_column_text(stmt, 4));
        printf("%s ", sqlite3_column_text(stmt, 5));
        printf("%s ", sqlite3_column_text(stmt, 6));
        printf("%s ", sqlite3_column_text(stmt, 7));
        printf("%s\n", sqlite3_column_text(stmt, 8));

        rc = sqlite3_step(stmt);

      }
  sqlite3_finalize(stmt);

    std::cout<<"\n";


      }

 string ans11;
   std::cout<< "Would you like to update a section's title? (yes or no): ";
   std::cin >> ans11;
   std::cout<<"\n";

   if(ans11 == "yes")
     {

   string Title;

   string crn;
   std::cout<<"Enter the CRN of the section's title you'd like to update(ex.12389421): ";
   std::cin >> crn;
   std::cout<<"\n";

   std::cout<<"Enter the new title of class: ";
   std:: cin >> Title;
   std::cout<<"\n";

     sql = "UPDATE Section SET TITLE = ?1 where CRN =?2;";

   rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

  if (rc != SQLITE_OK)
    {
   fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
   sqlite3_finalize(stmt);
    }

    rc = sqlite3_bind_text(stmt, 1, Title.c_str(), -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK)
      {
      fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
       sqlite3_finalize(stmt);
      }

    rc = sqlite3_bind_text(stmt, 2, crn.c_str(), -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK)
      {
      fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
       sqlite3_finalize(stmt);
      }

     rc = sqlite3_step(stmt);


    if (rc != SQLITE_ROW && rc != SQLITE_DONE)
      {
      fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);

      }

 else
      {
        fprintf(stdout, "Operation done successfully\n");
        sqlite3_finalize(stmt);
      }

 std::cout << "Sections:" << endl;

   sql = "SELECT * FROM Section";

   rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

  if (rc != SQLITE_OK)
    {
   fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
   sqlite3_finalize(stmt);
    }

     rc = sqlite3_step(stmt);

    if (rc != SQLITE_ROW && rc != SQLITE_DONE)
      {
      fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);

      }

    while(rc == SQLITE_ROW)
      {
        printf("%s ", sqlite3_column_text(stmt, 0));
        printf("%s ", sqlite3_column_text(stmt, 1));
        printf("%s ", sqlite3_column_text(stmt, 2));
        printf("%s ", sqlite3_column_text(stmt, 3));
        printf("%s ", sqlite3_column_text(stmt, 4));
        printf("%s ", sqlite3_column_text(stmt, 5));
        printf("%s ", sqlite3_column_text(stmt, 6));
        printf("%s ", sqlite3_column_text(stmt, 7));
        printf("%s\n", sqlite3_column_text(stmt, 8));

        rc = sqlite3_step(stmt);


    sqlite3_finalize(stmt);

    std::cout<<"\n";


      }

 string ans6;
   std::cout<< "Would you like to update a student's name? (yes or no): ";
   std::cin >> ans6;
   std::cout<<"\n";

   if(ans6 == "yes")
     {

       

   string sid;
   std::cout<<"Enter the SID of the student's name you'd like to update(ex.59681): ";
   std::cin >> sid;
   std::cout<<"\n";
   string sname;
   std::cout<<"Enter the new name(ex.John Meredith): ";
   std:: cin >> sname;
   std::cout<<"\n";

     sql = "UPDATE Student SET SNAME = ?1 where SID =?2;";

   rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

  if (rc != SQLITE_OK)
    {
   fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
   sqlite3_finalize(stmt);
    }

     rc = sqlite3_bind_text(stmt, 1, sname.c_str(), -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK)
      {
      fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
       sqlite3_finalize(stmt);
      }

   
    rc = sqlite3_bind_text(stmt, 2, sid.c_str(), -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK)
      {
      fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
       sqlite3_finalize(stmt);
      }

     rc = sqlite3_step(stmt);

     if (rc != SQLITE_ROW && rc != SQLITE_DONE)
      {
      fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);

      }

 else
      {
        fprintf(stdout, "Operation done successfully\n");
        sqlite3_finalize(stmt);
      }
 sql = "SELECT * FROM Student";

   rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

  if (rc != SQLITE_OK)
    {
   fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
   sqlite3_finalize(stmt);
    }

     rc = sqlite3_step(stmt);

    if (rc != SQLITE_ROW && rc != SQLITE_DONE)
      {
      fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);

      }

    while(rc == SQLITE_ROW)
      {
        printf("%s ", sqlite3_column_text(stmt, 0));
        printf("%s ", sqlite3_column_text(stmt, 1));
      

        rc = sqlite3_step(stmt);

      }
    sqlite3_finalize(stmt);

    std::cout<<"\n";

      }

 string ans7;
   std::cout<< "Would you like to update a professor's name? (yes or no): ";
   std::cin >> ans7;
   std::cout<<"\n";

   if(ans7 == "yes")
     {

    

   string pid;
   std::cout<<"Enter the PID of the professor's name you'd like to update(ex.55621): ";
   std::cin >> pid;
   std::cout<<"\n";
   string pname;
   std::cout<<"Enter the new name(ex.Ben): ";
   std:: cin >> pname;
   std::cout<<"\n";

     sql = "UPDATE Professor SET PNAME = ?1 where CRN =?2;";

   rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

  if (rc != SQLITE_OK)
    {
   fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
   sqlite3_finalize(stmt);
    }

    rc = sqlite3_bind_text(stmt, 2, pname.c_str(), -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK)
      {
      fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
       sqlite3_finalize(stmt);
      }

  
    rc = sqlite3_bind_text(stmt, 2, pid.c_str(), -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK)
      {
      fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
       sqlite3_finalize(stmt);
      }

     rc = sqlite3_step(stmt);

  if (rc != SQLITE_ROW && rc != SQLITE_DONE)
      {
      fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);

      }

 else
      {
        fprintf(stdout, "Operation done successfully\n");
        sqlite3_finalize(stmt);
      }
  
 sql = "SELECT * FROM Professor";

   rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

  if (rc != SQLITE_OK)
    {
   fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
   sqlite3_finalize(stmt);
    }

     rc = sqlite3_step(stmt);

    if (rc != SQLITE_ROW && rc != SQLITE_DONE)
      {
      fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);

      }

    while(rc == SQLITE_ROW)
      {
        printf("%s ", sqlite3_column_text(stmt, 0));
        printf("%s ", sqlite3_column_text(stmt, 1));
  

        rc = sqlite3_step(stmt);

      }
    sqlite3_finalize(stmt);

    std::cout<<"\n";

      }
     }
        
   //DATABASE CLOSES
    sqlite3_close(db);


}
