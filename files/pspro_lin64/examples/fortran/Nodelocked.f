      program Nodelocked

      include 'psprolib.inc'

!/*******************************************************************************************
!*
!* Check for a node-locked "monitor" license, version "5.0" 
!*
!*******************************************************************************************/


      integer ret, daysRemaining
      character*1024 szMessage

      ! make this application use an external license file
      ret = sgSetAttrInt(SG_ATTR_LICENSETYPE,SG_LICENSETYPE_EXTERNAL)

      ! the @ symbol tells the software the license file is next to this executable.

      ret = sgAuthorized('@monitor.lic','monitor','5.0')
      if (ret .ne. SG_AUTHORIZED) then
        ! tell the user they are not licensed for the application and exit gracefully
        ret =  sgGetLastErrorString(szMessage)
        print *,szMessage(:charlen(szMessage))
        stop
      end if

      ret = sgExpireDays('@monitor.lic','monitor','5.0',daysRemaining)
    
      write (*,'(A,I4,A)') ' Enabling the monitor functionality for ',    &
     &daysRemaining,' days....'
    
      print *,'Running the monitor application....'
    
      end program
