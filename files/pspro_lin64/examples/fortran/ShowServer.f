      program ShowServer

      include 'psprolib.inc'

!/******************************************************************
!*
!* This example demonstrates the sgShowServer() function.
!* It retrieves information from the license server about
!* components that the server is serving up.
!*
!******************************************************************/
      integer retVal,count,current
      character*1024 msg
      character*256 id
      character*128 certificate
      character*12  expires
      character*20  idtype
      character*12  version
      character*16  component

      retVal = sgSetAttrInt(SG_ATTR_LICENSETYPE,SG_LICENSETYPE_FLOATING)

      retVal = sgConnect()
      if (retVal .ne. SG_SUCCESS) then
        retVal = sgGetLastErrorString(msg)
        write(*,'(A)') msg(:charlen(msg))
        stop
      end if

      do
        retVal = sgShowServer(component,version,id,idtype,count,current,&
     &                        expires,certificate)
        if (retVal .eq. SG_NO_MORE_SERVER_COMPONENTS) goto 10
   
        write(*,'(8A,I4,A,I4,4A)')component(:charlen(component)),' ',   &
     &                            version(:charlen(version)),' ',       &
     &                            id(:charlen(id)),' ',                 &
     &                            idtype(:charlen(idtype)),' ',         &
     &                            count,' ',                            &
     &                            current,' ',                          &
     &                            expires(:charlen(expires)),' ',       &
     &                            certificate(:charlen(certificate))

      end do
  10  continue

      retVal = sgDisconnect()

      end program
