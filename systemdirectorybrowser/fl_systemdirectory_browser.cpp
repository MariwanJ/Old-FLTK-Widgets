//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Fl_SystemDirectory_Browser.cpp     v 0.0.1                              2006-06-19 
//
//         for the Fast Light Tool Kit (FLTK) 1.1.x .
//
// Copyright 1998-2003 by Mariwan Jalal, Don Zimmer, Bill Spitzak   & others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems to "fltk_kurdi@yahoo.com".
//
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


// This file is creating the Main widget which is the System Direcotry File Manager
#include "fl_systemdirectory_browser.h" 

 using namespace std;

//////////////////////////////////////////////////////////////////////
 // Callback when the item selected or + - used                      /
//////////////////////////////////////////////////////////////////////

int Fl_SystemDirectory_Browser::HandleSelect(Fl_Ext_TreeItem *pItemClicked, int bState)       // Callback Select
{
    { // START -- This part update the direcotries under the item .. it update one level under the shown itemes
    

      Fl_Ext_TreeItem *pSubDirHideScan=0;  
  {
      if (bState)
      {   // one click open it or close it the tree
          fl_cursor(FL_CURSOR_WAIT, (Fl_Color)0, (Fl_Color)0);
          Fl::check(); // this added because in linux it dose not show the right curser until you call this
          {
             Fl_Ext_TreeItem* scanDir=pItemClicked->m_pNext; //  ScanPointer 
             if (scanDir!=0)
             {
             while ((scanDir->m_nLevel>pItemClicked->m_nLevel) )
             {
                 if ((scanDir->m_nLevel>pItemClicked->m_nLevel)&&(scanDir->m_nLevel<pItemClicked->m_nLevel+2))
                   {
                       UpdateDirList(scanDir); // Update the subdirectories.
                       pSubDirHideScan=scanDir->m_pNext; 
		       if (!(pSubDirHideScan==0))
		       {
                        while((scanDir->m_nLevel<pSubDirHideScan->m_nLevel)) 
                          {
                                    pSubDirHideScan->m_bVisible=0;           
                                    pSubDirHideScan=pSubDirHideScan->m_pNext;
				    if( pSubDirHideScan==0) 
				      break;
                          }
                        }            
                   }
                     scanDir=scanDir->m_pNext;
		     if (scanDir==0)
		       break;
                } 
                
               }
           }
      }   
      ; //do nothing
     }
     }// END -- This part update the direcotries under the item .. it update one level under the shown itemes


// show normal curse again
 fl_cursor(FL_CURSOR_DEFAULT, (Fl_Color)0, (Fl_Color)0);
 
return 1;
}
//////////////////////////////////////////////////////////////////////
// Works  when double click occure on the item  -- left to the user  / 
//////////////////////////////////////////////////////////////////////
int Fl_SystemDirectory_Browser::HandleInvoke(Fl_Ext_TreeItem *ItemSquareClicked)        
{
    // just update the sub branch without selecting.

return 1;
}


//////////////////////////////////////////////////////////////////////
// Works when right click occure  -- left to the user
//////////////////////////////////////////////////////////////////////

int Fl_SystemDirectory_Browser::HandleMenu(void *pData)         // Callback  Right click mouse clicked
{
  
  return 1; 
}

 
// class constructor
Fl_SystemDirectory_Browser::Fl_SystemDirectory_Browser(int x , int y, int w, int h, const char *l):
                                                      Fl_Ext_TreeBrowser(x,y,w,h,l)
{
      box(FL_PLASTIC_DOWN_BOX);
      has_scrollbar(3);
      color(FL_BACKGROUND2_COLOR);
      selection_color(FL_SELECTION_COLOR);
      labeltype(FL_NORMAL_LABEL);
      labelfont(0);
      labelsize(12);
      labelcolor(FL_BLACK);
      textsize(12);
      align(FL_ALIGN_BOTTOM);                                                         
                                                      
Fl_Ext_TreeBrowser::type(FL_HOLD_BROWSER);

DriverLoad("") ; // Load System Hardisk or cd rom or ..etc the items. not any further subDir

// Here we should retrive the hole system directories.and sub. directories
Fl_Ext_TreeItem *pRetriveDirecFirst= Fl_Ext_TreeBrowser::item_first(); // which is the desktop

// Here we retrive SubDir under each drive so we can se the rectangel of the tree
Fl_Ext_TreeItem *scanDir =pRetriveDirecFirst;
             // The first drive;
  while (!(scanDir== 0))
	  {
           scanDir= scanDir->m_pNext;
           Fl_Ext_TreeItem *pSaveScanDir=scanDir;
           char* PathNameString= GetItemToDirectory(scanDir); //get the name of the item
	       
	   if ((strlen (PathNameString))==0) 
	     continue;
       scanDir=this->DirectoryLoad (PathNameString, scanDir); // Try to load sub items
	   if (!(strlen(PathNameString)==0))
              delete [] PathNameString;
	   else
	      if (PathNameString)
	        delete PathNameString;
       
       
       if (scanDir==pSaveScanDir) 
	           continue;
	    else 
	        if (scanDir!=0)
			 {
			 ;
			 }
           else 
          {
              scanDir=pSaveScanDir; 
          }
	 
	  }
    (item_first())->SetBranchVisible(0);
 }
 
 
// class destructor
Fl_SystemDirectory_Browser::~Fl_SystemDirectory_Browser()
{
// put your code here
}

int						// O - Number of files loaded
Fl_SystemDirectory_Browser::DriverLoad(const char  *directory)	// I - Directory to load 
{

  int		num_files;			// Number of files in directory
//  int		num_dirs;			// Number of directories in list
  char		filename[4096];			// Current file

  Fl_Ext_TreeBrowser::clear();         /// this come from Fl_Group mariwan clear the list
 // directory_ = directory;               // if specified, the function will retrive the dir of the specified place
  Fl_Ext_TreeItem *TempForTest=0;        // Temprorary pointer just for checking
#ifdef WIN32                 // level     name      icon         itembase
                           //nLevel, char *label, int x, Fl_Ext_TreeItem* pItemBase)
  TempForTest=  this->add_item(0   ,"Desktop"    ,1         ,0);        // This should be always available.
#else 
  TempForTest=this->add_item  (0,    "Desktop",   1         ,0);        // This should be always available.
  TempForTest=this->add_item  (1,          "/",  FL_TREE_ITEM_HARDDISK ,0);        // This should be always available.
#endif  



    // Retrive the Driver 
    //
    // No directory specified; for UNIX list all mount points.  For DOS
    // list all valid drive letters...
    //

    num_files = 0;

#ifdef WIN32
#  ifdef __CYGWIN__
    //
    // Cygwin provides an implementation of setmntent() to get the list
    // of available drives...
    //
    FILE          *m = setmntent("/-not-used-", "r");
    struct mntent *p;

    while ((p = getmntent (m)) != NULL) 
		{// this hould be fixed Mariwan
         //            level   item        icon                  item base-not nessisary here
     	 TempForTest=this->add_item(1,p->mnt_dir,FL_TREE_ITEM_HARDDISK ,0);    /// Add Item to the Browser
          num_files ++;            /// Increase nr of files
		}

    endmntent(m);                // Close the mntent
#  else
    //
    // Normal WIN32 code uses drive bits...
    //
    DWORD	drives;		// Drive available bits

    drives = GetLogicalDrives();          /// Get Drivers
    for (int i = 'A'; i <= 'Z'; i ++, drives >>= 1)
      if (drives & 1)
      {
        sprintf(filename, "%c:", i);

	  if (i < 'C'){
		  TempForTest=this->add_item(1,filename,FL_TREE_ITEM_FLOPPY,0);            /// Add Driver names 

	     }
	  else
	  {
	    TempForTest=this->add_item(1,filename,FL_TREE_ITEM_HARDDISK,0);          /// Add files 
         num_files ++;
        
      }
      
      }

#  endif // __CYGWIN__
#elif defined(__EMX__)
    //
    // OS/2 code uses drive bits...
    //
    ULONG	curdrive;	// Current drive
    ULONG	drives;		// Drive available bits
    int		start = 3;      // 'C' (MRS - dunno if this is correct!)


    DosQueryCurrentDisk(&curdrive, &drives);           // Retrive Drivers
    drives >>= start - 1;
    for (i = 'A'; i <= 'Z'; i ++, drives >>= 1)
      if (drives & 1)
      {            // Add to the browser
        sprintf(filename, "%c:/", i);
        if (i<'C' )
          TempForTest=this->add_item(1,filename,Fl_Ext_TreeItem::FL_TREE_ITEM_FLOPPY,0);
        else 
          TempForTest=this->add_item(1,filename,Fl_Ext_TreeItem::FL_TREE_ITEM_HARDDISK,0);
 	    num_files ++;
 	    
      }
#elif defined(__APPLE__) && !defined(__MWERKS__)
    // MacOS X and Darwin use getfsstat() system call...
    int			numfs;	// Number of file systems
    struct statfs	*fs;	// Buffer for file system info


    numfs = getfsstat(NULL, 0, MNT_NOWAIT);
    if (numfs > 0) 
    {
      // We have file systems, get them...
      fs = new struct statfs[numfs];
      getfsstat(fs, sizeof(struct statfs) * numfs, MNT_NOWAIT);

      // Add filesystems to the list...
      for (i = 0; i < numfs; i ++) 
      {
        if (fs[i].f_mntonname[1]) 
        {
          snprintf(filename, sizeof(filename), "%s/", fs[i].f_mntonname);

          TempForTest=this->add_item(1,filename,Fl_Ext_TreeItem::FL_TREE_ITEM_FLOPPY,0);
        }
         else 
           {
             TempForTest=this->add_item(1,"/",Fl_Ext_TreeItem::FL_TREE_ITEM_HARDDISK,0);

            }
         num_files ++;
       }

      // Free the memory used for the file system info array...
      if (fs)
        delete [] fs;
    }
#else


//this is for linux  I decided to avoid retriving the fstab file .. since it need hard work in avoding multiplication of the item tree
; // so do nothing


#endif // WIN32 || __EMX__

  /// The load recieved a directory .. End of driver section mariwan
  return (num_files);    // Return nomber of files loaded to the Browser  NOTE:this will not be real as we do not scan the whole hardisk
}





//////////////////////////////////////////////////////////////////////////////////
// Retrive all subdirectories in the drive                                      /
/////////////////////////////////////////////////////////////////////////////////
Fl_Ext_TreeItem* Fl_SystemDirectory_Browser::DirectoryLoad( char  *PathOrDriver, Fl_Ext_TreeItem * pItemBase)
{

if (pItemBase==0) 
	{ 
	// this is an error .. it should not happen that you send itembase zero!!
	return 0;
	}
  dirent	**files;	// Files in in directory
  int		i;				// Looping var
  int		num_files;			// Number of files in directory
  int		num_dirs;			// Number of directories in list
  char		filename[4096];			// Current file

  Fl_File_Sort_F *sort=fl_alphasort; // jare mauiati .. mariwan
  Fl_Ext_TreeItem *pItemRet=0;
    //
    // Build the file list...
    //


//   directory_=PathOrDriver;

	int SaveLevel= pItemBase->m_nLevel;

#if (defined(WIN32) && !defined(__CYGWIN__)) || defined(__EMX__)

    strlcpy(filename, PathOrDriver, sizeof(filename));
    i = strlen(filename) - 1;
    
	
    if (i == 2 && filename[1] == ':' && (filename[2] == '/' || filename[2] == '\\'))
		;
         else 
           if (filename[i] != '/' && filename[i] != '\\')
	   ;

    num_files = fl_filename_list(filename, &files, sort);

#else
    num_files = fl_filename_list(PathOrDriver, &files, sort);
#endif /* WIN32 || __EMX__ */

    if (num_files <= 0) /// what should I return
        //  Directory is Zero .. why? 
		   return pItemBase; // why??

    for (int i = 0, num_dirs = 0; i < num_files; i ++)
	{   
	   
      if ((strcmp(files[i]->d_name, ".") && strcmp(files[i]->d_name, "./"))) /// I will negelect this Mariwan
      {
	      
	      snprintf(filename, sizeof(filename), "%s/%s", PathOrDriver, files[i]->d_name);

#if defined(WIN32) && !defined(__CYGWIN__)
	     if (files[i]->d_name[strlen(files[i]->d_name) - 1] == '/') // Take only directories
 	      {
						
              files[i]->d_name[strlen(files[i]->d_name) - 1] = '\0';   //OK testim kird
			  char*TestForError=files[i]->d_name;

			  if ((strcmp(TestForError,".." )))
				  {

                                    pItemRet=this->add_item(SaveLevel+1,files[i]->d_name,FL_TREE_ITEM_FOLDER,pItemBase);

                                    num_dirs ++;
                                    pItemBase=pItemRet;
				  }
           }
#else
	      if (fl_filename_isdir(filename))
	       {
	               char name[1024]; // Temporary directory name
         	        snprintf(name, sizeof(name), "%s", files[i]->d_name); 

                   num_dirs ++;
		   char*TestForError=name;
		    if ((strcmp(TestForError,".." )))
                       pItemRet=this->add_item(SaveLevel+1,name,FL_TREE_ITEM_FOLDER,pItemBase);
		       pItemBase=pItemRet;
	        }
#endif // WIN32 && !__CYGWIN__
        
         }
    if ((files[i]))
         free(files[i]);
     }
     if (files)
       free(files);

return pItemRet;
}




// Function to return the path name from the drive name
  char* Fl_SystemDirectory_Browser::GetItemToDirectory(Fl_Ext_TreeItem *pCurrentItem) 
{

 char* PathNameString=0;  
 if (!(pCurrentItem==0)) 
 { // if not the item is hardisk or root dir
   if (!(pCurrentItem->m_nLevel<1))
    {
     Fl_Ext_TreeItem* temp=pCurrentItem; // temprary pointer to search to the root
     int maxv=0;
     while (!( temp->m_nLevel<1))
      {
        maxv=maxv+3+(strlen(temp->GetName()));  // Calulate the Max size of the path string
          if (temp->GetParent())                                                          // the one is for / between the directories
           {
             if ((temp->GetParent())->m_nLevel!=0 ) // if m_nlevel <>0 then get the parent
               {
                 temp=temp->GetParent();
               }
            else
               break;
           }  
         else
            break;
     }
   
     if (!(maxv==0))
     {
        PathNameString= new char [maxv];

        snprintf(PathNameString,1,"\0");  //Reset the array .... avoiding error?!!
        temp=pCurrentItem;
        char * Txtdes=0;
        while (!(temp->m_nLevel<1)) //  search for the path 
        {
          Txtdes=temp->GetName();

          if (!(strlen(PathNameString)<=1)) // if not the string is null or the char saved is \0
	       {
            char * temp1=new char [strlen(PathNameString)+1]; // allocate memeory for the temprary string pointer
            strcpy(temp1,PathNameString);  // copy the old value  (save it)
	        snprintf(PathNameString,strlen(PathNameString)+1,"\0");   // Reset the memory allocated 
	        strncat (PathNameString,Txtdes, strlen(Txtdes)+strlen(PathNameString));// Append the value to the Pointer PathNameString
#if (defined(WIN32) && !defined(__CYGWIN__)) || defined(__EMX__)
	        strncat(PathNameString, "\\", 1); // Append the value to the Pointer PathNameString

#else
                
		;
		
		if (!(temp->m_nLevel<2))
	          strncat(PathNameString, "/", 1); // Append the value to the Pointer PathNameString

#endif              
	          strncat(PathNameString, temp1, strlen(PathNameString)+strlen(temp1));  //Append the value to the pointer
                 if (!(strlen(temp1)==0))
                     delete [] temp1;
	                     
             }
         else
             { // if it is just a root item
             strncat (PathNameString,Txtdes, strlen(Txtdes)+strlen(PathNameString));
#if (defined(WIN32) && !defined(__CYGWIN__)) || defined(__EMX__)
			 
	         strncat(PathNameString, "\\", strlen(PathNameString)+1); // Append the value to the Pointer PathNameString
			 
#else  
                   ;
	         strncat(PathNameString, "/", strlen(PathNameString)+1); // Append the value to the Pointer PathNameString
#endif

            }   
          if (temp->GetParent())
             temp=temp->GetParent();
          else 
             break; // should not be nessisary but I write it to avoid a bug
         }

   return PathNameString ;
   
    }
    else 
    {
    // max is Zero ... why?
     return"";
       
    }
   }
   else
   {// the pCurrentItem->m_nLevel <1
       // this should not be happend but I will write my code avoiding bugs.
       int GetSizeofTheString=0;
       GetSizeofTheString=strlen(pCurrentItem->GetName())+1;
       PathNameString =new char [GetSizeofTheString]; // get the lenght of the string and allocate memory
       strcpy(PathNameString,pCurrentItem->GetName());
       return  PathNameString;                   // return the result.
    }
// in case it is the Base item liek "/" or "c:" ...etc

 }
else 
 {
         // pCurrentItem was pointing to ziro  
    return ""; // Here whe get an item which is zero so the return value is nothing     
 }
  
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////                Update one item 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Fl_SystemDirectory_Browser::UpdateDirList(Fl_Ext_TreeItem *FromItem )
{
    
  Fl_Ext_TreeItem * pCleanItem= FromItem;
  pCleanItem=pCleanItem->m_pNext;
  
  if (!(pCleanItem==0))
   {
     while ((pCleanItem->m_nLevel>FromItem->m_nLevel) )
      {

        Remove(pCleanItem);
        pCleanItem=FromItem->m_pNext;
	
	if ((pCleanItem==0)) 
	  break;
     }
   
  }
 

  Fl_Ext_TreeItem *scanDir = FromItem;
  char* PathNameString= GetItemToDirectory(scanDir); //get the name of the item
  if ((strlen (PathNameString))==0) 
	    return 0;
  else
        scanDir=this->ItemToDirectoryUpdate(PathNameString, scanDir); // Try to load sub items

	   if (!(strlen(PathNameString)==0))
              delete [] PathNameString;
	   else
	      if (PathNameString)
	        delete PathNameString;
       return 1; // ok
}



//**********************************************************************************************
//**********************************************************************************************
//              Adding new directory connecting to the  base                                   *
//**********************************************************************************************
//**********************************************************************************************

Fl_Ext_TreeItem* Fl_SystemDirectory_Browser::ItemToDirectoryUpdate( char  *PathOrDriver, Fl_Ext_TreeItem * pItemBase)
{

if (pItemBase==0) 
	{ 
	// this is an error .. it should not happen that you send itembase zero!!
	return 0;
	}
  dirent	**files;	// Files in in directory
  int		i;				// Looping var
  int		num_files;			// Number of files in directory
  int		num_dirs;			// Number of directories in list
  char		filename[4096];			// Current file

  Fl_File_Sort_F *sort=fl_alphasort; // jare mauiati .. mariwan
  Fl_Ext_TreeItem *pItemRet=0;
    //
    // Build the file list...
    //


	int SaveLevel= pItemBase->m_nLevel;

#if (defined(WIN32) && !defined(__CYGWIN__)) || defined(__EMX__)

    strlcpy(filename, PathOrDriver, sizeof(filename));
    i = strlen(filename) - 1;
    
    num_files = fl_filename_list(filename, &files, sort);
    
#else
    num_files = fl_filename_list(PathOrDriver, &files, sort);
#endif /* WIN32 || __EMX__ */

    if (num_files <= 0) /// what should I return?
        // directory was zero?? .. I should neglect it!!!!?
		   return pItemBase; // why??
		

    for (i = 0, num_dirs = 0; i < num_files; i ++)
	{   
	   
      if ((strcmp(files[i]->d_name, ".") && strcmp(files[i]->d_name, "./"))) /// I will negelect this Mariwan
      {
	        snprintf(filename, sizeof(filename), "%s/%s", PathOrDriver, files[i]->d_name);
		      

#if defined(WIN32) && !defined(__CYGWIN__)
	     if (files[i]->d_name[strlen(files[i]->d_name) - 1] == '/') // Take only directories
 	      {
						
              files[i]->d_name[strlen(files[i]->d_name) - 1] = '\0';   //OK 
			  char*TestForError=files[i]->d_name;

			  if ((strcmp(TestForError,".." )))
				  {
				     
				     if (!CheckIfTheTreeHasThisItem(files[i]->d_name,pItemBase))
				     {

                        pItemRet=this->add_item(SaveLevel+1,files[i]->d_name,FL_TREE_ITEM_FOLDER,pItemBase);
                        num_dirs ++;
                        pItemBase=pItemRet;
                     } 
				  }
           }
#else
	      if (fl_filename_isdir(filename))
	       {
            char name[1024]; // Temporary directory name
         	snprintf(name, sizeof(name), "%s", files[i]->d_name); 
            num_dirs ++;
		    char*TestForError=name;
		    if ((strcmp(TestForError,".." )))

	             if (!CheckIfTheTreeHasThisItem(name,pItemBase))
                       {
		        pItemRet=this->add_item(SaveLevel+1,name,FL_TREE_ITEM_FOLDER,pItemBase);
	               }
		}
#endif // WIN32 && !__CYGWIN__
        
         }
    if ((files[i]))
         free(files[i]);
     }
     if (files)
       free(files);

return pItemRet;
}

// check if the item is available in the list
int Fl_SystemDirectory_Browser::CheckIfTheTreeHasThisItem(char *pItemToCheck, Fl_Ext_TreeItem * pItemBaseToCheckedItem)
{
    int Result=0;
    Fl_Ext_TreeItem * pScanItem=0;
    
    if (pItemBaseToCheckedItem->m_nLevel<=2)
	  {
               pScanItem=pItemBaseToCheckedItem;
	  }
    else
	 {
               // to get the first item in the subtree
            pScanItem=(pItemBaseToCheckedItem->GetParent())->m_pNext;  // take the first item in the subtree
	 }

	 Fl_Ext_TreeItem *pRealBasePoint = pScanItem->m_pPrev;
     if(pScanItem!=0)
		 

     while ((pScanItem->m_nLevel> pItemBaseToCheckedItem->m_nLevel))
		 { 
           if(strcmp(pScanItem->GetName(),pItemToCheck))

			   {
			   	 
                  Result=1;
                  break;                                                   
			   }
          else
			  {
                  pScanItem=pScanItem->m_pNext;
				  Result=0;
			  }
		 }
     return Result;    
	}
