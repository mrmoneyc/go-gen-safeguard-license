      program Floating

      include 'psprolib.inc'

!/*******************************************************************************************
!*
!* Check out a "monitor" license, version "5.0" from the license server
!*
!* The server will have to be running and serving this license.
!*
!*******************************************************************************************/


      character*1024 szMessage
      integer retVal
      external myRecon,myReconCheckoutFail,myReconComplete
      external myReconExit
      integer myRecon,myReconCheckoutFail,myReconComplete
      integer myReconExit


      ! make this application use a floating license server
      retVal = sgSetAttrInt(SG_ATTR_LICENSETYPE,SG_LICENSETYPE_FLOATING)

      ! Set callbacks just in case we loose connection with the license server
      retVal = sgSetAttrFnF(SG_ATTR_VENDOR_RECONNECT,myRecon)
      retVal = sgSetAttrFnF(SG_ATTR_VENDOR_RECONNECT_COMPLETE,          &
     &                     myReconComplete)
      retVal = sgSetAttrFnF(SG_ATTR_VENDOR_RECONNECT_CHECKOUT_FAIL,     &
     &                     myReconCheckoutFail)
      retVal = sgSetAttrFnF(SG_ATTR_VENDOR_RECONNECT_EXIT,myReconExit)

      retVal = sgCheckout('monitor','5.0')
      if (retVal .ne. SG_SUCCESS) then
        ! tell the user they are not licensed and exit gracefully
        retVal = sgGetLastErrorString(szMessage);
        print *, szMessage(:charlen(szMessage))
        stop
      end if

      print *,'Running the monitor application....'

      print *,'Press return to release the license....'
      read(*,'(A)') szMessage

      ! app is finished, check in the license.  NOTE:  it is not necessary to do this
      ! as the license server will detect the process terminating and do it for you.

      retVal = sgCheckin('monitor','5.0');

      end program

      ! These are the callback functions for when the client (this program) looses connection
      ! with the license server.  See the "ProgrammerGuide.pdf" for more information.
      ! This give you control over what to do when a connection is lost with the license server
      ! They are not necessary.  However, if you don't implement them, the default handlers behave
      ! almost the same as these in this example.  If you had a GUI program, you would want to
      ! do something more than just calling write(*,*)

      !/*********************************************************
      !* Lost connection to the license server
      !*********************************************************/

      integer function myRecon(server,retries,retrycount)
      include 'psprolib.inc'
      character*(*) server
      integer retries, retrycount
      write(*,'(3A,I2,A,I2,A)')                                         &
     &' myRecon: Lost connection with license server ',                 &
     &  server(:charlen(server)),' Attempting to reconnect ',           &
     &  retries,' of ',retrycount,' ....'
      return 
      end

      !/*********************************************************
      !* reconnected, but one or more of the licenses cannot be re-checked out
      !*********************************************************/

      integer function myReconCheckoutFail(server,component,version)
      include 'psprolib.inc'
      character*(*) server,component,version
      write(*,'(6A)')                                                   &
     &' myRecon: While reconnecting to the license server ',            &
     &  server(:charlen(server)),                                       &
     &' unable to re-checkout the license for ',                        &
     &  component(:charlen(component)),                                 &
     &' version ',version(:charlen(version))
      return 
      end

      !/*********************************************************
      !* called when successfully reconnected to the license server
      !*********************************************************/

      integer function myReconComplete(server,retrycount)
      include 'psprolib.inc'
      character*(*) server
      integer retrycount
      write(*,'(3A,I2,A)')                                              &
     &' myRecon: Reconnected to the license server ',                   &
     &  server(:charlen(server)),                                       &
     &' after ',retrycount,' attempts ....'
      return 
      end

      !/*********************************************************
      !* bad news.  could not reconnect to the license server
      !*********************************************************/

      integer function myReconExit(server,retrycount)
      include 'psprolib.inc'
      character*(*) server
      integer retrycount
      write(*,'(3A,I2,A)')                                              &
     &' myRecon: Failed to reeconnect to the license server ',          &
     &  server(:charlen(server)),                                       &
     &' after ',retrycount,' attempts .... Exiting.'
      stop
      return 
      end
