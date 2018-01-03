      program ShowClient

      include 'psprolib.inc'

!/******************************************************************
!*
!* This example demonstrates the sgShowClient() function.
!* It retrieves information about what the current process
!* has checked out.
!*
!******************************************************************/
      integer retVal,count;
      character*1024 msg
      character*256 serverhost,clienthost
      character*64 user
      character*16 component
      character*12 version

      retVal = sgSetAttrInt(SG_ATTR_LICENSETYPE,SG_LICENSETYPE_FLOATING)

      retVal = sgCheckout("Monitor","5.0");
      if (retVal .ne. SG_SUCCESS) then
        retVal = sgGetLastErrorString(msg)
        write(*,'(A)') msg(:charlen(msg))
        stop
      end if

      ! IMPORTANT:  Even thought the version for "widget" is 6.0 in the license file
      ! if we check out an earlier version and only a 6.0 license is available it will
      ! consume one of the 6.0 licenses

      ret = sgCheckout('widget','5.0')
      if (ret .ne. SG_SUCCESS) then
        retVal = sgGetLastErrorString(msg)
        write(*,'(A)') msg(:charlen(msg))
        stop
      end if

      ! IMPORTANT!!  if you check out the same component again, the count will increment
      ret = sgCheckout('widget','5.0')
      if (ret .ne. SG_SUCCESS) then
        retVal = sgGetLastErrorString(msg)
        write(*,'(A)') msg(:charlen(msg))
        stop
      end if

      do
          retVal = sgShowClient(serverhost,clienthost,user,component,   &
     &                          version,count)
     
          if (retVal .eq. SG_NO_MORE_CLIENT_COMPONENTS) goto 10

          write(*,'(10A,I4)') serverhost(:charlen(serverhost)),' ',     &
     &                       clienthost(:charlen(clienthost)),' ',      &
     &                       user(:charlen(user)),' ',                  &
     &                       component(:charlen(component)),' ',        &
     &                       version(:charlen(version)),' ',            &
     &                       count
 
      end do
  10  continue
     
      retVal = sgCheckin('monitor','5.0')
     
      ! NOTE:  Even if you don't check-in the second "widget", it will be 
      ! returned to the license pool when the process exits.
     
      retVal = sgCheckin('widget','5.0')
      end program
