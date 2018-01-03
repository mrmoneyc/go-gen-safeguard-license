      program PASfloating

      include 'psprolib.inc'

!//********************************************************************
!//*
!//* This sample demonstrates a real life scenario of using the Product
!//* Activation Server for a typical client application.  It first checks
!//* whether there is a paid license available, if there is, it will 
!//* retrieve it.  If not, then it will attempt to obtain a demo license.
!//* available and all criteria are met, then a demo license will be 
!//* installed on the client computer next to this running executable.
!//*
!//* This example checks for a license called "monitor" "5.0".
!//*
!//* If you are testing this on your local host you won't need to change
!//* the hostname in the two locations below.  If not, you will need to
!//* change "localhost" to either an IP address or Domain name.
!//*
!//* MySQL and the Prodcut Activation Server will need to be running,
!//* and either of the "paid_float" or "demo_float" table records
!//* will need to be updated to add the above component name, version, and
!//* other information to enable this client app to get a license.  If you
!//* use bin/create.sql to create the database and tables, these will be
!//* populated for you.
!//*
!//********************************************************************


      character*256 email
      character*16 component
      character*12 version
      character*128 licensefile
      character*128 company
      character*128 serverline
      character*1024 componentline
      character*1024 szMessage
      integer retVal
      integer daysRemaining

      email = 'bob@example.com'
      component = 'monitor'
      version = '5.0'
      licensefile = 'pas-floating.lic'
      company = 'localhost'

      write(*,'(A,A,A)') ' Checking for a paid floating license to run '&
     &                  ,component(:charlen(component)), '.'

      ! we are going to use the email address as the unique paid customer identifier
      ! it can be anything.  But the email address "bob@example.com" must be in the
      ! cust column of the paid_float table to identify the customer.

      retVal = sgPaActivate(company, 29775, SG_ACTIVATE_PAID_FLOAT,email&
     &                ,component,version,email,serverline,componentline)

      if (retVal .ne. SG_SUCCESS) then

        write(*,'(3A)') ' Checking for a demo floating license to run ' &
     &                   ,component(:charlen(component)), '.'
        retVal = sgPaActivate(company, 29775, SG_ACTIVATE_DEMO_FLOAT,'' &
     &                ,component,version,email,serverline,componentline)

        if (retVal .ne. SG_SUCCESS) then
          retVal = sgGetLastErrorString(szMessage)
          write (*,'(A,A)') ' Problem with the activation server: ',    &
     &                        szMessage(:charlen(szMessage))
          stop
        end if
      end if

      
      write(*,'(3A)') ' Here is your floating license file for the '    &
     &               ,component(:charlen(component)),' application.'
      write(*,'(A)') serverline(:charlen(serverline))
      write(*,'(A)') componentline(:charlen(componentline))

      write(*,'(A)') ' We have saved it as pas-floating.lic'

      open(unit=10,file='pas-floating.lic',form='FORMATTED',            &
     &     status='REPLACE',action='WRITE')

      write(10,'(A)') serverline(:charlen(serverline))
      write(10,'(A)') componentline(:charlen(componentline))

      close(unit=10)

!// Using the PAS to get a floating license file is just as easy as getting a 
!// node-locked license file.  Getting it set up so client applications can
!// access the licese server and use the new license file, depends on several things.
!//
!// - Is the license server even running ?
!// - If it is, where is it? On this machine or on a different system?
!// - Depending on your Operating System (Windows, Linux, OS X, etc.), you will
!//   want to set up the license server differently.  For example, on Windows, you
!//   probably want to install sglmd.exe as a Windows Service.  On OS X, launchd.
!//   
!// - So at this point the process may become more manual.  Refer to the 
!//   LicenseManagerGuide.pdf for instructions on setting up the floating 
!//   license server.


      end program
