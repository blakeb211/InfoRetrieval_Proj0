
Here is a possible process for completing this project:

1. The first thing to do is define a strategy for identifying terms in the documents. 
Make a list of all the stop-words you can think of, and write a function that reads through the words in the files,
 saves the terms, and eliminates the stop-words. You may have to add more stop-words to your list as you 
 review the list of terms from an iteration.

2. Write Boost test cases to test your function, and a makefile to bring everything together for your build.

3. Check your files into CVS, particularly if you are working with partners.

4. Add processing to include location data, that is, which file and where in the file is a term located?
You may want to figure out a calculation to define page number or paragraph number.

5. Write Boost test cases to test this additional functionality.

6. Create an inverted index and store the location data in each term's record.

7. Write test cases.

8. Design an interface to allow a user to enter a query.

9. Using the search algorithm described above, process the inverted index and return the location data to the user.

10. Be sure to include test cases for this final part as well.


Working Notes Step 1:
  Create Stopwords txt file - done
  Assign docIds to the documents - done
  Write function to load the stopwords - done
  Function 1. Read through the words in the files. Save the terms. Remove the stop words. - done
  Add location data - done
  Write tests using Google Test
  Write a user interface
  Add a search function ****
  OPTIONAL:
		Add a custom allocator to be able to report the size of the inverted index
		Add method to serialize the map to disk  - Might be better as a separate project

  INSTALL NOTES
  Boost directory is c:\boost172
  Boost Compilation Instructions:
    bootstrap.bat
    b2 -j8 toolset=msvc-14.2 address-model=64 architecture=x86 link=static threading=multi runtime-link=shared --build-type=complete

  Add c:\boost172 to the Additional Include Directories
  Add c:\boost172\stage\lib to the Additional Library Directories
  
  
NOTEPAD++ NPPEXEC Command To Build On The Fly
npp_save
cd $(CURRENT_DIRECTORY)
clang++ -I c:\boost172 -L c:\boost172\stage\lib -llibboost_system-vc142-mt-gd-x64-1_72.lib *.cpp
cmd /c $(CURRENT_DIRECTORY)\a.exe