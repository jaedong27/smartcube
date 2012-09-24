Public Class frmMain

    '정답 플래그
    '한번이라도 정답을 표시하면 더이상 계산하지 않음
    Dim answerflag As Boolean = False

    '통신 프로토콜 데이타
    Dim eui(8) As Byte
    Dim BoardID As Byte
    Dim wall(4) As Byte
    Dim LM_status As Byte
    '2byte
    Dim LM_value As Integer
    '4byte
    Dim LM_Gyro As Integer

    Dim Red As Byte
    Dim Green As Byte
    Dim Blue As Byte

    Dim BoardEui(10, 4) As Byte

    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        cmbPortname.SelectedIndex = 13
        cmbBaudrate.SelectedIndex = 1
        cmbValue.SelectedIndex = 0
        Timer.Enabled = False
        CheckForIllegalCrossThreadCalls = False

        eui(0) = Long.Parse("0", Globalization.NumberStyles.HexNumber)
        eui(1) = Long.Parse("D", Globalization.NumberStyles.HexNumber)
        eui(2) = Long.Parse("6F", Globalization.NumberStyles.HexNumber)
        eui(3) = Long.Parse("0", Globalization.NumberStyles.HexNumber)


        BoardEui(1, 0) = Long.Parse("00", Globalization.NumberStyles.HexNumber)
        BoardEui(1, 1) = Long.Parse("BA", Globalization.NumberStyles.HexNumber)
        BoardEui(1, 2) = Long.Parse("96", Globalization.NumberStyles.HexNumber)
        BoardEui(1, 3) = Long.Parse("D2", Globalization.NumberStyles.HexNumber)

        BoardEui(2, 0) = Long.Parse("00", Globalization.NumberStyles.HexNumber)
        BoardEui(2, 1) = Long.Parse("BB", Globalization.NumberStyles.HexNumber)
        BoardEui(2, 2) = Long.Parse("6D", Globalization.NumberStyles.HexNumber)
        BoardEui(2, 3) = Long.Parse("D9", Globalization.NumberStyles.HexNumber)

        BoardEui(3, 0) = Long.Parse("00", Globalization.NumberStyles.HexNumber)
        BoardEui(3, 1) = Long.Parse("AC", Globalization.NumberStyles.HexNumber)
        BoardEui(3, 2) = Long.Parse("4C", Globalization.NumberStyles.HexNumber)
        BoardEui(3, 3) = Long.Parse("37", Globalization.NumberStyles.HexNumber)

        BoardEui(4, 0) = Long.Parse("00", Globalization.NumberStyles.HexNumber)
        BoardEui(4, 1) = Long.Parse("BA", Globalization.NumberStyles.HexNumber)
        BoardEui(4, 2) = Long.Parse("78", Globalization.NumberStyles.HexNumber)
        BoardEui(4, 3) = Long.Parse("39", Globalization.NumberStyles.HexNumber)

        BoardEui(6, 0) = Long.Parse("00", Globalization.NumberStyles.HexNumber)
        BoardEui(6, 1) = Long.Parse("5C", Globalization.NumberStyles.HexNumber)
        BoardEui(6, 2) = Long.Parse("3C", Globalization.NumberStyles.HexNumber)
        BoardEui(6, 3) = Long.Parse("F5", Globalization.NumberStyles.HexNumber)

        BoardEui(7, 0) = Long.Parse("00", Globalization.NumberStyles.HexNumber)
        BoardEui(7, 1) = Long.Parse("BA", Globalization.NumberStyles.HexNumber)
        BoardEui(7, 2) = Long.Parse("96", Globalization.NumberStyles.HexNumber)
        BoardEui(7, 3) = Long.Parse("B6", Globalization.NumberStyles.HexNumber)

        'Debug.Print(eui(1))
    End Sub

    Private Sub butOpen_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles butOpen.Click
        If SerialPort.IsOpen Then
            MsgBox("already Open")
            Return
        End If

        SerialPort.PortName = cmbPortname.Text
        SerialPort.BaudRate = cmbBaudrate.Text

        SerialPort.Open()
        'Timer.Enabled = True
        initReceiveData()
    End Sub

    Private Sub frmMain_Resize(ByVal sender As Object, ByVal e As System.EventArgs) Handles Me.Resize
        tabPage.Width = Me.Width - 40
        tabPage.Height = Me.Height - 100
        picture.Width = tabPage.Width - 10
        picture.Height = tabPage.Height - 10
        GroupBox2.Height = tabPage.Height - GroupBox2.Location.Y - 30
        txtDebugStatus.Height = GroupBox2.Height - txtDebugStatus.Location.Y - 10
        txtDebug.Height = tabPage.Height - 40
        txtDebugAscill.Height = tabPage.Height - 40
        txtDebugAscill.Width = tabPage.Width - txtDebugAscill.Location.X - 10
    End Sub

    Dim predata As Byte
    Dim receiveddata(250) As Byte
    Dim dataindex As Integer
    Dim datastatus As Integer

    Public Function initReceiveData()
        dataindex = 0
        datastatus = 0
    End Function

    Dim updatecompletflag(10) As Boolean
    Dim boardconfirmdata(10) As Integer
    Public Function CompleteData()
        'txtDebugStatus.Text = txtDebugStatus.Text + vbCrLf + dataindex.ToString + vbCrLf + "Complete"

        'txtDebugStatus.Text = txtDebugStatus.Text + vbCrLf
        'txtDebugStatus.Text = txtDebugStatus.Text + Hex(receiveddata(0)) + ":"

        'If receiveddata(1) <> 0 Then
        'txtDebugStatus.Text = txtDebugStatus.Text + Hex(receiveddata(1))
        'End If

        'txtDebugStatus.Text += ":"

        'If receiveddata(2) <> 0 Then
        'txtDebugStatus.Text = txtDebugStatus.Text + Hex(receiveddata(2))
        'End If

        'txtDebugStatus.Text += ":"

        'If receiveddata(3) <> 0 Then
        'txtDebugStatus.Text = txtDebugStatus.Text + Hex(receiveddata(3))
        'End If

        'txtDebugStatus.Text += ":"

        'If receiveddata(4) <> 0 Then
        'txtDebugStatus.Text = txtDebugStatus.Text + Hex(receiveddata(4))
        'End If

        'txtDebugStatus.Text += vbCrLf

        Dim temp(4) As Byte
        temp(0) = receiveddata(1)
        temp(1) = receiveddata(2)
        temp(2) = receiveddata(3)
        temp(3) = receiveddata(4)
        NumberGameMakeAttachTable(receiveddata(0), temp)
        Dim index As Integer

        txtDebugStatus.Text = ""

        'Dim Gyro_x As Integer = temp(7)
        'Dim Gyro_y As Integer = temp(8)
        'Dim Gyro_z As Integer = temp(9)

        'txtDebugStatus.Text += Gyro_x.ToString + ":"
        'txtDebugStatus.Text += Gyro_y.ToString + ":"
        'txtDebugStatus.Text += Gyro_z.ToString + vbCrLf
        Dim tempint As Integer
        If receiveddata(0) > 176 And receiveddata(0) < 196 Then
            tempint = (receiveddata(0) - 176) \ 2
            'debug용
            boardconfirmdata(tempint) = receiveddata(6)

            If BoardValue(tempint) = receiveddata(6) And receiveddata(6) <> 0 Then
                updatecompletflag(tempint) = True
            End If

            If updatecompletflag(tempint) = False Then
                If BoardValue(tempint) <> 0 Then
                    'SendBoardGameStatus(tempint, BoardValue(tempint))
                    Debug.Print(BoardValue(tempint))
                Else
                    'SendBoardGameStatus(tempint, 10)
                    Debug.Print(0)
                End If
            End If

        End If

        For index = 0 To 9
            txtDebugStatus.Text = txtDebugStatus.Text + index.ToString + ":" + BoardIDtoAttachID(index, 0).ToString _
                                      + BoardIDtoAttachID(index, 1).ToString _
                                       + BoardIDtoAttachID(index, 2).ToString _
                                    + BoardIDtoAttachID(index, 3).ToString _
                                    + "     " + boardconfirmdata(index).ToString + vbCrLf
        Next
        If answerflag = False Then
            NumberGameCheckAnswer()
        End If
    End Function


    Public Function ReceiveData(ByVal data As Byte)
        Select Case (datastatus)
            Case 0
                If (predata = 1 And data = 2) Then
                    datastatus = 1
                End If
            Case 1
                If (data = 1) Then
                    If predata = 1 Then
                        receiveddata(dataindex) = 1
                        dataindex = dataindex + 1
                        predata = 250
                    End If
                Else
                    If (predata = 1 And data = 3) Then
                        'end packet
                        If dataindex = 14 Then
                            CompleteData()
                        Else

                        End If
                        datastatus = 0
                        initReceiveData()
                    Else
                        receiveddata(dataindex) = data
                        dataindex = dataindex + 1
                    End If
                End If
        End Select

        predata = data
        Return 0
    End Function

    Private Sub SerialPort_DataReceived(ByVal sender As Object, ByVal e As System.IO.Ports.SerialDataReceivedEventArgs) Handles SerialPort.DataReceived
        Dim length As Integer

        length = SerialPort.BytesToRead()

        Dim index As Integer
        Dim byttemp As Byte
        For index = 1 To length
            byttemp = SerialPort.ReadByte()

            ReceiveData(byttemp)

            If chkDebug.Checked Then
                txtDebugAscill.Text = txtDebugAscill.Text + Chr(byttemp)
                If chkHex.Checked Then
                    txtDebug.Text = txtDebug.Text + Hex(byttemp) + vbCrLf
                Else
                End If
            End If
        Next
    End Sub
    Private Sub butSend_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles butSend.Click
        If chkSendEui.Checked Then
            eui(0) = (nudEui1.Value \ 256) Mod 256
            eui(1) = (nudEui1.Value) Mod 256
            eui(2) = (nudEui2.Value \ 256) Mod 256
            eui(3) = (nudEui2.Value) Mod 256

            eui(4) = (nudEui3.Value \ 256) Mod 256
            eui(5) = (nudEui3.Value) Mod 256
            eui(6) = (nudEui4.Value \ 256) Mod 256
            eui(7) = (nudEui4.Value) Mod 256
        End If

        BoardID = 180

        wall(0) = chkSendUp.Checked
        wall(1) = chkSendDown.Checked
        wall(2) = chkSendLeft.Checked
        wall(3) = chkSendRight.Checked

        LM_status = nudsendlmstatus.Value
        LM_value = cmbValue.SelectedIndex
        LM_Gyro = 102

        Red = 200
        Green = 100
        Blue = 50

        If chkSendEui.Checked Then
            SendRequestData(True)
        Else
            SendRequestData(False)
        End If
    End Sub

    Public Function SendDLEFormat(ByVal data() As Byte, ByVal length As Integer)
        'Serial 포트를 우선 체크
        If SerialPort.IsOpen Then

        Else
            Return 0
        End If

        Dim buffer(250) As Byte
        Dim index As Integer
        Dim lengthloopindex As Integer

        'start parket
        buffer(0) = 1
        buffer(1) = 2

        index = 2

        For lengthloopindex = 0 To length - 1
            If data(lengthloopindex) = 1 Then
                buffer(index) = 1
                index = index + 1
                buffer(index) = 1
            Else
                buffer(index) = data(lengthloopindex)
            End If
            index = index + 1
        Next

        'end parket
        buffer(index) = 1
        index = index + 1
        buffer(index) = 3
        index = index + 1

        SerialPort.Write(buffer, 0, index)
    End Function

    Public Function SendRequestData(ByVal SendCheckEui As Boolean)
        Dim temp(200) As Byte
        Dim index As Integer

        'Dim eui(8) As Byte
        'Dim BoardID As Byte
        'Dim wall(4) As Byte
        'Dim LM_status As Byte
        ''2byte
        'Dim LM_value As Integer
        ''4byte
        'Dim LM_Gyro As Integer
        '
        'Dim Red As Byte
        'Dim Green As Byte
        'Dim Blue As Byte

        If (SendCheckEui = True) Then
            'eui
            temp(0) = eui(7)
            temp(1) = eui(6)
            temp(2) = eui(5)
            temp(3) = eui(4)
            temp(4) = eui(3)
            temp(5) = eui(2)
            temp(6) = eui(1)
            temp(7) = eui(0)
            index = 8
        Else
            index = 0
        End If

        temp(index) = BoardID
        index = index + 1

        temp(index) = wall(0)
        index = index + 1

        temp(index) = wall(1)
        index = index + 1

        temp(index) = wall(2)
        index = index + 1

        temp(index) = wall(3)
        index = index + 1

        temp(index) = LM_status
        index = index + 1

        temp(index) = LM_value
        index = index + 1

        temp(index) = (LM_Gyro \ (256 * 256 * 256)) Mod 256
        index = index + 1
        temp(index) = (LM_Gyro \ (256 * 256)) Mod 256
        index = index + 1
        temp(index) = (LM_Gyro \ (256)) Mod 256
        index = index + 1
        temp(index) = LM_Gyro Mod 256
        index = index + 1

        temp(index) = Red
        index = index + 1
        temp(index) = Blue
        index = index + 1
        temp(index) = Green
        index = index + 1

        SendDLEFormat(temp, index)
    End Function

    Private Sub butClose_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles butClose.Click
        If SerialPort.IsOpen Then
            SerialPort.Close()
        End If
    End Sub

    Private Sub butClear_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles butClear.Click
        txtDebug.Text = ""
        txtDebugAscill.Text = ""
    End Sub

    Dim predisplaystatus As Integer = 9999
    Dim predisplaynumber As Integer = 1000
    'status
    ' 0 = 아무것도 아님
    ' 1 = 정답
    ' 2 = 틀림
    Public Function PictureDisplayNumber(ByVal number As Integer, ByVal status As Integer, ByVal gangjeupdate As Boolean)
        'Dim myBrush As New System.Drawing.SolidBrush(System.Drawing.Color.FromArgb())
        Dim myBrush As New System.Drawing.SolidBrush(System.Drawing.Color.Black)
        Dim myBigFontBrush As New System.Drawing.SolidBrush(System.Drawing.Color.Orange)
        Dim mySmallFontBrush As New System.Drawing.SolidBrush(System.Drawing.Color.Yellow)
        Dim formGraphics As System.Drawing.Graphics

        Dim fontNumber As New System.Drawing.Font("맑은 고딕", picture.Height / 3)
        Dim fontText As New System.Drawing.Font("맑은 고딕", picture.Height / 10)

        If predisplaynumber = number And status = predisplaystatus And gangjeupdate = False Then
            '업로드 할 필요가 없음
            Return 0 '
        End If

        formGraphics = picture.CreateGraphics()
        formGraphics.FillRectangle(myBrush, New Rectangle(0, 0, picture.Width, picture.Height))
        formGraphics.TextRenderingHint = Drawing.Text.TextRenderingHint.AntiAlias

        'number = -800
        If number > 1000 Then
            formGraphics.DrawString(number.ToString, fontNumber, myBigFontBrush, picture.Width / 2 - 510, picture.Height / 2 - 400)
        ElseIf number > 100 Then
            formGraphics.DrawString(number.ToString, fontNumber, myBigFontBrush, picture.Width / 2 - 400, picture.Height / 2 - 400)
        ElseIf number > 10 Then
            formGraphics.DrawString(number.ToString, fontNumber, myBigFontBrush, picture.Width / 2 - 290, picture.Height / 2 - 400)
        ElseIf number >= 0 Then
            formGraphics.DrawString(number.ToString, fontNumber, myBigFontBrush, picture.Width / 2 - 180, picture.Height / 2 - 400)
        ElseIf number > -10 Then
            formGraphics.DrawString(number.ToString, fontNumber, myBigFontBrush, picture.Width / 2 - 260, picture.Height / 2 - 400)
        ElseIf number > -100 Then
            formGraphics.DrawString(number.ToString, fontNumber, myBigFontBrush, picture.Width / 2 - 380, picture.Height / 2 - 400)
        ElseIf number > -1000 Then
            formGraphics.DrawString(number.ToString, fontNumber, myBigFontBrush, picture.Width / 2 - 490, picture.Height / 2 - 400)
        Else
            formGraphics.DrawString(number.ToString, fontNumber, myBigFontBrush, picture.Width / 2 - 600, picture.Height / 2 - 400)
        End If

        'status = 1
        Select Case status
            Case 0
                '아무것도 아님
            Case 1
                '정답임
                formGraphics.DrawString("정답!", fontText, mySmallFontBrush, picture.Width / 2 - 150, picture.Height / 2 + 100)
                If TimerRestart.Enabled <> True Then
                    TimerRestart.Enabled = True
                End If
            Case 2
                '틀림
                'formGraphics.DrawString("정답이 아닙니다!", fontText, mySmallFontBrush, picture.Width / 2 - 300, picture.Height / 2)
        End Select

        predisplaynumber = number
        predisplaystatus = status

        myBrush.Dispose()
        formGraphics.Dispose()
    End Function

    Public Function SendBoardGameStatus(ByVal BoardNumber As Byte, ByVal BoardValue As Byte)
        Dim i As Integer
        For i = 0 To 3
            eui(i + 4) = BoardEui(BoardNumber, i)
        Next
        LM_status = 2
        LM_value = Boardvalue
        SendRequestData(True)
    End Function

    Public Function NumberGameStart()
        My.Computer.Audio.Play("게임방.wav")
        NumberGameMakeAnswer()
        TimerSendValue.Enabled = True
    End Function

    Dim BoardIDtoAttachID(10, 4) As Byte
    Dim BoardAnswer(10, 4) As Byte
    Dim BoardValue(40) As Integer
    Dim NumberGameAnswer As Integer
    Public Function NumberGameMakeAnswer()
        Dim number(3) As Integer
        Dim symbol(2) As Byte
        Dim lastblockposition As Integer
        Dim i As Integer

        '문제 체크하는 플래그 내려두기
        answerflag = False

        '문제 만들고
        VBMath.Randomize()
        For i = 0 To 2
            number(i) = VBMath.Rnd * 8 + 1
            '   Debug.Print(number(i))
        Next

        For i = 0 To 1
            symbol(i) = VBMath.Rnd * 2 + 11
            '    Debug.Print(symbol(i))
            If symbol(i) = 13 Then
                symbol(i) = 14
            End If
        Next

        BoardValue(0) = 15 '이퀄8

        txtAnswer.Text = ""

        '답 계산하고
        Select Case symbol(0)
            Case 11 '더하기
                NumberGameAnswer = number(0) + number(1)
                txtAnswer.Text = number(0).ToString + "+" + number(1).ToString
            Case 12 '빼기
                NumberGameAnswer = number(0) - number(1)
                txtAnswer.Text = number(0).ToString + "-" + number(1).ToString
            Case 14 '곱하기
                NumberGameAnswer = number(0) * number(1)
                txtAnswer.Text = number(0).ToString + "*" + number(1).ToString
        End Select


        Select Case symbol(1)
            Case 11 '더하기
                NumberGameAnswer += number(2)
                txtAnswer.Text += "+" + number(2).ToString
            Case 12 '빼기
                NumberGameAnswer -= number(2)
                txtAnswer.Text += "-" + number(2).ToString
            Case 14 '곱하기
                NumberGameAnswer *= number(2)
                txtAnswer.Text += "*" + number(2).ToString
        End Select

        'lastblockposition = VBMath.Rnd * 1

        'Select Case lastblockposition
        '   Case 0
        'Select Case symbol(0)
        '    Case 11 '더하기
        'NumberGameAnswer += number(3)
        'txtAnswer.Text += "+" + number(3).ToString
        '    Case 12 '빼기
        'NumberGameAnswer -= number(3)
        'txtAnswer.Text += "-" + number(3).ToString
        '    Case 14 '곱하기
        'NumberGameAnswer *= number(3)
        'txtAnswer.Text += "*" + number(3).ToString
        'End Select
        '    Case 1
        'Select Case symbol(1)
        '    Case 11 '더하기
        'NumberGameAnswer += number(3)
        'txtAnswer.Text += "+" + number(3).ToString
        '    Case 12 '빼기
        'NumberGameAnswer -= number(3)
        'txtAnswer.Text += "-" + number(3).ToString
        '    Case 14 '곱하기
        'NumberGameAnswer *= number(3)
        'txtAnswer.Text += "*" + number(3).ToString
        'End Select
        'End Select


        '화면에 표시
        PictureDisplayNumber(NumberGameAnswer, 0, False)

        Dim j As Integer

        '현재 가진 보드는 1,2,3,5,6,7
        Dim reservedindex(6) As Boolean
        Dim indextoboardnumber(6) As Integer
        For j = 0 To 5
            reservedindex(j) = False
        Next

        'indextoboardnumber(0) = 1
        'indextoboardnumber(1) = 2
        'indextoboardnumber(2) = 3
        'indextoboardnumber(3) = 4
        'indextoboardnumber(4) = 6
        'indextoboardnumber(5) = 7


        indextoboardnumber(0) = 1
        indextoboardnumber(1) = 3
        indextoboardnumber(2) = 4
        indextoboardnumber(3) = 6
        indextoboardnumber(4) = 7

        Dim randomindex As Integer

        '숫자 넣는것 Board에 넣어줌
        Dim k As Integer

        '숫자가 3개
        For j = 0 To 2
            randomindex = VBMath.Rnd * 4
            For k = 0 To 4
                randomindex += 1
                If randomindex >= 5 Then
                    randomindex = 0
                End If
                If reservedindex(randomindex) = False Then
                    reservedindex(randomindex) = True
                    BoardValue(indextoboardnumber(randomindex)) = number(j)
                    Exit For
                Else

                End If
            Next
        Next

        '기호를 BoardValue에 넣어줌
        For j = 0 To 1
            randomindex = VBMath.Rnd * 4
            For k = 0 To 4
                randomindex += 1
                If randomindex >= 4 Then
                    randomindex = 0
                End If
                If reservedindex(randomindex) = False Then
                    reservedindex(randomindex) = True
                    BoardValue(indextoboardnumber(randomindex)) = symbol(j)
                    Exit For
                Else

                End If
            Next
        Next

        'Debug.Print(number(0))
        'Debug.Print(symbol(0))
        'Debug.Print(number(1))
        'Debug.Print(symbol(1))
        'Debug.Print(number(2))
        'Debug.Print(number(3))

        'Debug.Print(BoardValue(1))
        'Debug.Print(BoardValue(2))
        'Debug.Print(BoardValue(3))
        'Debug.Print(BoardValue(4))
        'Debug.Print(BoardValue(6))
        'Debug.Print(BoardValue(7))

        For j = 0 To 10
            updatecompletflag(j) = False
        Next


        '문제 보드에 뿌려주고
        '업로드 안되는 경우때문에 3번씩 보내줌
        'For j = 0 To 1
        'For k = 0 To 5
        'If BoardValue(indextoboardnumber(k)) <> 0 Then
        'SendBoardGameStatus(indextoboardnumber(k), BoardValue(indextoboardnumber(k)))
        'Else
        'SendBoardGameStatus(indextoboardnumber(k), 10)
        'End If
        'System.Threading.Thread.Sleep(30)
        'Next
        'Next
    End Function

    Public Function NumberGameCheckAnswer() As Boolean
        Dim prevalue As Integer
        Dim index = 0
        Dim index2 = 0
        Dim currentpointindex
        Dim wallnumber = 0
        Dim findstartpointflag As Boolean = False
        Dim calnumber As Integer = 0

        For index = 0 To 9
            wallnumber = 0
            For index2 = 0 To 3
                If BoardIDtoAttachID(index, index2) <> 0 Then
                    wallnumber += 1
                End If
            Next
            If wallnumber = 1 And BoardIDtoAttachID(index, 3) <> 0 Then
                findstartpointflag = True
                Exit For
            End If
        Next

        If findstartpointflag = False Then
            '시작점 못찾음
            Return 0
        End If

        If BoardIDtoAttachID(index, 3) > 10 Then
            '시작 지점이 숫자가 아님 기호임
            Return 0
        End If

        txtDebugStatus.Text += vbCrLf + "start:" + index.ToString

        '시작점 = index
        currentpointindex = index
        calnumber = BoardValue(currentpointindex)
        prevalue = 0 'equal
        For index = 0 To 5


            'txtDebugStatus.Text += vbCrLf + "pre:" + prevalue.ToString
            txtDebugStatus.Text += vbCrLf + "nowindex:" + currentpointindex.ToString
            'txtDebugStatus.Text += vbCrLf + "cal:" + calnumber.ToString

            If currentpointindex > 10 Then
                '통신 잘못인듯'
                Return 0
            End If

            If BoardValue(prevalue) > 10 Then
                '이전 값이 심볼임
                If BoardValue(currentpointindex) > 10 Then
                    '현재값도 심볼이면 답이 안됨
                    txtDebugStatus.Text += vbCrLf + "nosymbol:" + calnumber.ToString
                    Return 0
                End If
            Else
                '이전 값이 숫자임
                If BoardValue(currentpointindex) <= 10 Then
                    '이전값이 숫자인데 이번에도 숫자이면 말이 안됨
                    txtDebugStatus.Text += vbCrLf + "nonumber:" + calnumber.ToString
                    Return 0
                End If
            End If

            If BoardValue(currentpointindex) <= 10 Then
                '현재 위치가 숫자이면
                '이전 값이 심볼임 그래서 계산함

                '위아래도 여기서 처리해주면 됨
                Select Case BoardValue(prevalue)
                    Case 11
                        '더하기
                        calnumber += BoardValue(currentpointindex)
                        txtDebugStatus.Text += vbCrLf + "계산:+" + BoardValue(currentpointindex).ToString
                    Case 12
                        '빼기
                        calnumber -= BoardValue(currentpointindex)
                        txtDebugStatus.Text += vbCrLf + "계산:-" + BoardValue(currentpointindex).ToString
                    Case 14
                        '곱하기
                        calnumber *= BoardValue(currentpointindex)
                        txtDebugStatus.Text += vbCrLf + "계산:*" + BoardValue(currentpointindex).ToString
                End Select

                '이전 심볼 위에 값이 있는지 확인하고 더해주는 부분
                If BoardIDtoAttachID(prevalue, 0) <> 0 Then
                    Select Case BoardValue(prevalue)
                        Case 11
                            '더하기
                            calnumber += BoardValue(BoardIDtoAttachID(prevalue, 0))
                            txtDebugStatus.Text += vbCrLf + "계산:+" + BoardValue(BoardIDtoAttachID(prevalue, 0)).ToString
                        Case 12
                            '빼기
                            calnumber -= BoardValue(BoardIDtoAttachID(prevalue, 0))
                            txtDebugStatus.Text += vbCrLf + "계산:-" + BoardValue(BoardIDtoAttachID(prevalue, 0)).ToString
                        Case 14
                            '곱하기
                            calnumber *= BoardValue(BoardIDtoAttachID(prevalue, 0))
                            txtDebugStatus.Text += vbCrLf + "계산:*" + BoardValue(BoardIDtoAttachID(prevalue, 0)).ToString
                    End Select
                End If

                '이전 심볼 아래에 값이 있는지 확인하고 더해주는 부분
                If BoardIDtoAttachID(prevalue, 1) <> 0 Then
                    Select Case BoardValue(prevalue)
                        Case 11
                            '더하기
                            calnumber += BoardValue(BoardIDtoAttachID(prevalue, 1))
                            txtDebugStatus.Text += vbCrLf + "계산:+" + BoardValue(BoardIDtoAttachID(prevalue, 1)).ToString
                        Case 12
                            '빼기
                            calnumber -= BoardValue(BoardIDtoAttachID(prevalue, 1))
                            txtDebugStatus.Text += vbCrLf + "계산:-" + BoardValue(BoardIDtoAttachID(prevalue, 1)).ToString
                        Case 13
                            '곱하기
                            calnumber *= BoardValue(BoardIDtoAttachID(prevalue, 1))
                            txtDebugStatus.Text += vbCrLf + "계산:*" + BoardValue(BoardIDtoAttachID(prevalue, 1)).ToString
                    End Select
                End If
            End If

            If BoardIDtoAttachID(currentpointindex, 3) <> 0 Then
                '우측에 값이 있으면 다음 블럭도 존재 한다는 것
                '다음블럭으로 넘어감
                prevalue = currentpointindex
                currentpointindex = BoardIDtoAttachID(currentpointindex, 3)
            Else
                '우측에 값이 없다는 건 다음 블럭이 없다(이것이 끝!)
                '여기서 답 비교
                If calnumber = NumberGameAnswer And index > 3 Then
                    '맞음
                    txtDebugStatus.Text += vbCrLf + "정답" + calnumber.ToString
                    PictureDisplayNumber(NumberGameAnswer, 1, False)
                    My.Computer.Audio.Play("촤랑.wav")
                    '더이상 답 체크 하지 않음
                    answerflag = True
                    Return 1
                Else
                    '다름
                    txtDebugStatus.Text += vbCrLf + "틀림" + calnumber.ToString
                    PictureDisplayNumber(NumberGameAnswer, 2, False)
                    Return 0
                End If
            End If

            txtDebugStatus.Text += vbCrLf
        Next

        Return 0
    End Function

    Public Function NumberGameMakeAttachTable(ByVal BoardID As Byte, ByVal NeighBoardID() As Byte)

        If BoardID < 176 Then
            Debug.Print("Eui Fail")
            Return 0
        End If

        Dim index As Integer
        For index = 0 To 3
            If NeighBoardID(index) = 0 Or NeighBoardID(index) >= 176 Then

            Else
                Return 0
            End If
        Next

        BoardID = (BoardID - 176) \ 2

        If NeighBoardID(0) <> 0 Then
            '붙음
            BoardIDtoAttachID(BoardID, 0) = (NeighBoardID(0) - 176) \ 2
        Else
            '안붙음
            BoardIDtoAttachID(BoardID, 0) = 0
        End If

        If NeighBoardID(1) <> 0 Then
            '붙음
            BoardIDtoAttachID(BoardID, 1) = (NeighBoardID(1) - 176) \ 2
        Else
            '안붙음
            BoardIDtoAttachID(BoardID, 1) = 0
        End If

        If NeighBoardID(2) <> 0 Then
            '붙음
            BoardIDtoAttachID(BoardID, 2) = (NeighBoardID(2) - 176) \ 2
        Else
            '안붙음
            BoardIDtoAttachID(BoardID, 2) = 0
        End If

        If NeighBoardID(3) <> 0 Then
            '붙음
            BoardIDtoAttachID(BoardID, 3) = (NeighBoardID(3) - 176) \ 2
        Else
            '안붙음
            BoardIDtoAttachID(BoardID, 3) = 0
        End If
    End Function

    Private Sub picture_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles picture.Click
        NumberGameStart()
    End Sub

    Private Sub TimerRestart_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TimerRestart.Tick
        'NumberGameStart()
        'TimerRestart.Enabled = False
    End Sub

    Dim sendindex As Integer = 0
    Private Sub TimerSendValue_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TimerSendValue.Tick
        'Dim i As Integer
        'For i = 0 To 10
        'If BoardValue(i) > 0 And BoardValue(i) < 14 And updatecompletflag(i) = False Then
        'If BoardValue(i) <> 0 Then
        'SendBoardGameStatus(i, BoardValue(i))
        'Debug.Print(BoardValue(i))
        'Else
        'SendBoardGameStatus(i, 10)
        'Debug.Print(0)
        'End If
        'Return
        'End If
        'Next
        Dim indextoboardnumber(6) As Integer

        'indextoboardnumber(0) = 1
        'indextoboardnumber(1) = 2
        'indextoboardnumber(2) = 3
        'indextoboardnumber(3) = 4
        'indextoboardnumber(4) = 6
        'indextoboardnumber(5) = 7

        indextoboardnumber(0) = 1
        indextoboardnumber(1) = 3
        indextoboardnumber(2) = 4
        indextoboardnumber(3) = 6
        indextoboardnumber(4) = 7


        SendBoardGameStatus(indextoboardnumber(sendindex), BoardValue(indextoboardnumber(sendindex)))

        sendindex += 1
        If sendindex > 4 Then
            sendindex = 0
        End If

    End Sub

    Private Sub tabPage_DockChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles tabPage.DockChanged
        
    End Sub

    Private Sub tabPage_SelectedIndexChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles tabPage.SelectedIndexChanged
        If answerflag = True Then
            PictureDisplayNumber(NumberGameAnswer, 1, True)
        Else
            PictureDisplayNumber(NumberGameAnswer, 0, True)
        End If
    End Sub

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        'Serial 포트를 우선 체크
        If SerialPort.IsOpen Then

        Else
            Return
        End If

        Dim buffer(250) As Byte
        Dim index As Integer
        
        'start parket
        buffer(0) = 255
        buffer(1) = 254
        buffer(2) = 0
        buffer(3) = 255
        buffer(4) = 253
        buffer(5) = 13
        
        'buffer(0) = Asc("a")
        'buffer(1) = Asc("b")
        'buffer(2) = Asc("c")
        'buffer(3) = Asc("d")
        'buffer(4) = Asc("e")
        'buffer(5) = 13

        SerialPort.Write(buffer, 0, 1)
        SerialPort.Write(buffer, 1, 1)
        SerialPort.Write(buffer, 2, 1)
        SerialPort.Write(buffer, 3, 1)
        SerialPort.Write(buffer, 4, 1)
        SerialPort.Write(buffer, 5, 1)
    End Sub

    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        SerialPort.Write(NumericUpDown1.Value)
    End Sub

    Private Sub Button3_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button3.Click
        'Serial 포트를 우선 체크
        If SerialPort.IsOpen Then

        Else
            Return
        End If

        Dim buffer(250) As Byte
        Dim index As Integer

        'start parket
        buffer(0) = 255
        buffer(1) = 254
        buffer(2) = 1
        'ID
        buffer(3) = NumericUpDown3.Value
        'Index
        buffer(4) = NumericUpDown4.Value
        buffer(5) = 255
        buffer(6) = 253
        buffer(7) = 13

        'buffer(0) = Asc("a")
        'buffer(1) = Asc("b")
        'buffer(2) = Asc("c")
        'buffer(3) = Asc("d")
        'buffer(4) = Asc("e")
        'buffer(5) = 13

        SerialPort.Write(buffer, 0, 8)
    End Sub
End Class
