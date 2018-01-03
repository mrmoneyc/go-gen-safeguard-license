      program ShowDetail

      include 'psprolib.inc'

!/******************************************************************
!*
!* This example demonstrates the sgShowServerDetail() function.
!* It retrieves information from the license server about all 
!* components that are checked out and by whom.  Plus some other 
!* interesting information for immediate display purposes.
!*
!******************************************************************/
      integer retVal,thread_id,sockfd,pid,count
      character*1024 msg
      character*256 process
      character*256 host
      character*64 user
      character*16 ip
      character*16 component
      character*12 version

      retVal = sgSetAttrInt(SG_ATTR_LICENSETYPE,SG_LICENSETYPE_FLOATING)

      retVal = sgConnect()
      if (retVal .ne. SG_SUCCESS) then
        retVal = sgGetLastErrorString(msg)
        write(*,'(A)') msg(:charlen(msg))
        stop
      end if
     
      do
        retVal = sgShowServerDetail(thread_id,sockfd,ip,pid,process,    &
     &                              user,host,component,version,count)
        if (retVal .eq. SG_NO_MORE_SERVER_DETAIL) goto 10
     
        write(*,'(I6,A,I5,3A,I5,11A,I4)')thread_id,' ',                 &
     &                               sockfd,' ',                        &
     &                               ip(:charlen(ip)),' ',              &
     &                               pid,' ',                           &
     &                               process(:charlen(process)),' ',    &
     &                               user(:charlen(user)),' ',          &
     &                               host(:charlen(host)),' ',          &
     &                               component(:charlen(component)),' ',&
     &                               version(:charlen(version)),' ',    &
     &                               count
      end do
  10  continue
    
      retVal = sgDisconnect()
      end program
