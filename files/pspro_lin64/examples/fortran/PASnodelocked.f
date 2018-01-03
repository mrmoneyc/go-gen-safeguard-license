      program PASnodelocked

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
!//* and either of the "paid_node" or "demo_node" table records
!//* will need to be updated to add the above component name, version, and
!//* other information to enable this client app to get a license.  If you
!//* use bin/create.sql to create the database and tables, these will be
!//* populated for you.
!//*
!//********************************************************************/


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


      ! make this application use an external license file
      retVal = sgSetAttrInt(SG_ATTR_LICENSETYPE,SG_LICENSETYPE_EXTERNAL)

      write(*,'(3A)') ' Checking for a license to run ',                &
     &                component(:charlen(component)), '.'

      ! Are we already licensed?  
      retVal = sgAuthorized(licensefile,component,version)
      if (retVal .ne. SG_AUTHORIZED) then

      ! we are going to use the email address as the unique paid customer identifier
      ! it can be anything.  But the email address "bob@example.com" must be in the
      ! cust column of the paid_node table to identify the customer.

        write(*,'(3A)') ' Checking for a paid license to run ',         &
     &                  component(:charlen(component)),  '.'
        retVal = sgPaActivate(company, 29775, SG_ACTIVATE_PAID_NODE,    &
     &          email,component,version,email,serverline,componentline)

        if ((retVal.ne.SG_SUCCESS).and.(retVal.ne.SG_AUTHORIZED)) then

          write(*,'(3A)') ' Checking for a demo license to run ',       &
     &                    component(:charlen(component)), '.'
          retVal = sgPaActivate(company, 29775, SG_ACTIVATE_DEMO_NODE,  &
     &            '',component,version,email,serverline,componentline)

          if ((retVal.ne.SG_SUCCESS).and.(retVal.ne.SG_AUTHORIZED)) then
            retVal = sgGetLastErrorString(szMessage)
            write(*,'(2A)') ' Problem with the activation server: ',    &
     &                      szMessage(:charlen(szMessage))
            stop
          else
            ! create the license file
            retVal = sgEnableComponentLine(licensefile,componentline)
            if (retVal .ne. SG_SUCCESS) then
              retVal = sgGetLastErrorString(szMessage)
              write(*,'(2A)') ' Problem installing the license: ',      &
     &                      szMessage(:charlen(szMessage))
              stop
            end if
          end if

        else

          ! create the license file
          retVal = sgEnableComponentLine(licensefile,componentline)
          if (retVal .ne. SG_SUCCESS) then
            retVal = sgGetLastErrorString(szMessage)
            write(*,'(2A)') ' Problem installing the license: ',        &
     &                      szMessage(:charlen(szMessage))
            stop
          end if
        end if
      end if

      ! check once again in case the PAS sent us a new license file
      retVal = sgAuthorized(licensefile,component,version)
      if (retVal .ne. SG_SUCCESS) then
        retVal = sgGetLastErrorString(szMessage)
        write(*,'(A)') szMessage(:charlen(szMessage))
        stop
      end if
    
      ! create the int pointer
      retVal = sgExpireDays(licensefile,component,version,daysRemaining)
      write(*,'(3A,I4,A)') ' Authorized to run the demo version of ',   &
     &        component(:charlen(component)), ' for ',daysRemaining,    &
     &        ' more days.'

      end program
