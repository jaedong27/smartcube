<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class frmMain
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.SerialPort = New System.IO.Ports.SerialPort(Me.components)
        Me.Timer = New System.Windows.Forms.Timer(Me.components)
        Me.cmbBaudrate = New System.Windows.Forms.ComboBox()
        Me.cmbPortname = New System.Windows.Forms.ComboBox()
        Me.butOpen = New System.Windows.Forms.Button()
        Me.tabPage = New System.Windows.Forms.TabControl()
        Me.TabPage1 = New System.Windows.Forms.TabPage()
        Me.picture = New System.Windows.Forms.PictureBox()
        Me.TabPage2 = New System.Windows.Forms.TabPage()
        Me.txtDebugAscill = New System.Windows.Forms.TextBox()
        Me.GroupBox2 = New System.Windows.Forms.GroupBox()
        Me.butClear = New System.Windows.Forms.Button()
        Me.txtDebugStatus = New System.Windows.Forms.TextBox()
        Me.NumericUpDown1 = New System.Windows.Forms.NumericUpDown()
        Me.chkHex = New System.Windows.Forms.CheckBox()
        Me.chkDebug = New System.Windows.Forms.CheckBox()
        Me.chkReceiveDown = New System.Windows.Forms.CheckBox()
        Me.chkReceiveUp = New System.Windows.Forms.CheckBox()
        Me.chkReceiveLeft = New System.Windows.Forms.CheckBox()
        Me.chkReceiveRight = New System.Windows.Forms.CheckBox()
        Me.txtDebug = New System.Windows.Forms.TextBox()
        Me.GroupBox1 = New System.Windows.Forms.GroupBox()
        Me.Button2 = New System.Windows.Forms.Button()
        Me.NumericUpDown2 = New System.Windows.Forms.NumericUpDown()
        Me.Button1 = New System.Windows.Forms.Button()
        Me.cmbValue = New System.Windows.Forms.ComboBox()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.nudsendlmstatus = New System.Windows.Forms.NumericUpDown()
        Me.nudEui4 = New System.Windows.Forms.NumericUpDown()
        Me.nudEui3 = New System.Windows.Forms.NumericUpDown()
        Me.nudEui2 = New System.Windows.Forms.NumericUpDown()
        Me.nudEui1 = New System.Windows.Forms.NumericUpDown()
        Me.chkSendEui = New System.Windows.Forms.CheckBox()
        Me.numSendRGB = New System.Windows.Forms.NumericUpDown()
        Me.chkSendDown = New System.Windows.Forms.CheckBox()
        Me.chkSendUp = New System.Windows.Forms.CheckBox()
        Me.butSend = New System.Windows.Forms.Button()
        Me.chkSendLeft = New System.Windows.Forms.CheckBox()
        Me.chkSendRight = New System.Windows.Forms.CheckBox()
        Me.butClose = New System.Windows.Forms.Button()
        Me.TimerRestart = New System.Windows.Forms.Timer(Me.components)
        Me.txtAnswer = New System.Windows.Forms.TextBox()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.TimerSendValue = New System.Windows.Forms.Timer(Me.components)
        Me.Button3 = New System.Windows.Forms.Button()
        Me.NumericUpDown3 = New System.Windows.Forms.NumericUpDown()
        Me.NumericUpDown4 = New System.Windows.Forms.NumericUpDown()
        Me.tabPage.SuspendLayout()
        Me.TabPage1.SuspendLayout()
        CType(Me.picture, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.TabPage2.SuspendLayout()
        Me.GroupBox2.SuspendLayout()
        CType(Me.NumericUpDown1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.GroupBox1.SuspendLayout()
        CType(Me.NumericUpDown2, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.nudsendlmstatus, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.nudEui4, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.nudEui3, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.nudEui2, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.nudEui1, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.numSendRGB, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.NumericUpDown3, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.NumericUpDown4, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'SerialPort
        '
        '
        'cmbBaudrate
        '
        Me.cmbBaudrate.FormattingEnabled = True
        Me.cmbBaudrate.Items.AddRange(New Object() {"38400", "115200"})
        Me.cmbBaudrate.Location = New System.Drawing.Point(141, 12)
        Me.cmbBaudrate.Name = "cmbBaudrate"
        Me.cmbBaudrate.Size = New System.Drawing.Size(121, 20)
        Me.cmbBaudrate.TabIndex = 16
        '
        'cmbPortname
        '
        Me.cmbPortname.FormattingEnabled = True
        Me.cmbPortname.Items.AddRange(New Object() {"COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8", "COM9", "COM10", "COM11", "COM12", "COM13", "COM14", "COM15"})
        Me.cmbPortname.Location = New System.Drawing.Point(13, 12)
        Me.cmbPortname.Name = "cmbPortname"
        Me.cmbPortname.Size = New System.Drawing.Size(121, 20)
        Me.cmbPortname.TabIndex = 15
        '
        'butOpen
        '
        Me.butOpen.Location = New System.Drawing.Point(268, 12)
        Me.butOpen.Name = "butOpen"
        Me.butOpen.Size = New System.Drawing.Size(75, 23)
        Me.butOpen.TabIndex = 14
        Me.butOpen.Text = "Open"
        Me.butOpen.UseVisualStyleBackColor = True
        '
        'tabPage
        '
        Me.tabPage.Controls.Add(Me.TabPage1)
        Me.tabPage.Controls.Add(Me.TabPage2)
        Me.tabPage.Location = New System.Drawing.Point(12, 50)
        Me.tabPage.Name = "tabPage"
        Me.tabPage.SelectedIndex = 0
        Me.tabPage.Size = New System.Drawing.Size(1262, 828)
        Me.tabPage.TabIndex = 18
        '
        'TabPage1
        '
        Me.TabPage1.Controls.Add(Me.picture)
        Me.TabPage1.Location = New System.Drawing.Point(4, 22)
        Me.TabPage1.Name = "TabPage1"
        Me.TabPage1.Padding = New System.Windows.Forms.Padding(3)
        Me.TabPage1.Size = New System.Drawing.Size(1254, 802)
        Me.TabPage1.TabIndex = 0
        Me.TabPage1.Text = "Game"
        Me.TabPage1.UseVisualStyleBackColor = True
        '
        'picture
        '
        Me.picture.BackColor = System.Drawing.Color.Black
        Me.picture.Location = New System.Drawing.Point(0, 0)
        Me.picture.Name = "picture"
        Me.picture.Size = New System.Drawing.Size(1241, 538)
        Me.picture.TabIndex = 0
        Me.picture.TabStop = False
        '
        'TabPage2
        '
        Me.TabPage2.Controls.Add(Me.txtDebugAscill)
        Me.TabPage2.Controls.Add(Me.GroupBox2)
        Me.TabPage2.Controls.Add(Me.txtDebug)
        Me.TabPage2.Controls.Add(Me.GroupBox1)
        Me.TabPage2.Location = New System.Drawing.Point(4, 22)
        Me.TabPage2.Name = "TabPage2"
        Me.TabPage2.Padding = New System.Windows.Forms.Padding(3)
        Me.TabPage2.Size = New System.Drawing.Size(1254, 802)
        Me.TabPage2.TabIndex = 1
        Me.TabPage2.Text = "Debug"
        Me.TabPage2.UseVisualStyleBackColor = True
        '
        'txtDebugAscill
        '
        Me.txtDebugAscill.Location = New System.Drawing.Point(723, 6)
        Me.txtDebugAscill.Multiline = True
        Me.txtDebugAscill.Name = "txtDebugAscill"
        Me.txtDebugAscill.ScrollBars = System.Windows.Forms.ScrollBars.Vertical
        Me.txtDebugAscill.Size = New System.Drawing.Size(525, 512)
        Me.txtDebugAscill.TabIndex = 20
        '
        'GroupBox2
        '
        Me.GroupBox2.Controls.Add(Me.butClear)
        Me.GroupBox2.Controls.Add(Me.txtDebugStatus)
        Me.GroupBox2.Controls.Add(Me.NumericUpDown1)
        Me.GroupBox2.Controls.Add(Me.chkHex)
        Me.GroupBox2.Controls.Add(Me.chkDebug)
        Me.GroupBox2.Controls.Add(Me.chkReceiveDown)
        Me.GroupBox2.Controls.Add(Me.chkReceiveUp)
        Me.GroupBox2.Controls.Add(Me.chkReceiveLeft)
        Me.GroupBox2.Controls.Add(Me.chkReceiveRight)
        Me.GroupBox2.Location = New System.Drawing.Point(6, 207)
        Me.GroupBox2.Name = "GroupBox2"
        Me.GroupBox2.Size = New System.Drawing.Size(359, 765)
        Me.GroupBox2.TabIndex = 18
        Me.GroupBox2.TabStop = False
        Me.GroupBox2.Text = "Recieve"
        '
        'butClear
        '
        Me.butClear.Location = New System.Drawing.Point(245, 78)
        Me.butClear.Name = "butClear"
        Me.butClear.Size = New System.Drawing.Size(75, 23)
        Me.butClear.TabIndex = 12
        Me.butClear.Text = "화면초기화"
        Me.butClear.UseVisualStyleBackColor = True
        '
        'txtDebugStatus
        '
        Me.txtDebugStatus.Font = New System.Drawing.Font("Gulim", 15.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(129, Byte))
        Me.txtDebugStatus.Location = New System.Drawing.Point(6, 194)
        Me.txtDebugStatus.Multiline = True
        Me.txtDebugStatus.Name = "txtDebugStatus"
        Me.txtDebugStatus.ScrollBars = System.Windows.Forms.ScrollBars.Vertical
        Me.txtDebugStatus.Size = New System.Drawing.Size(347, 401)
        Me.txtDebugStatus.TabIndex = 11
        '
        'NumericUpDown1
        '
        Me.NumericUpDown1.Location = New System.Drawing.Point(15, 156)
        Me.NumericUpDown1.Name = "NumericUpDown1"
        Me.NumericUpDown1.Size = New System.Drawing.Size(191, 21)
        Me.NumericUpDown1.TabIndex = 9
        '
        'chkHex
        '
        Me.chkHex.AutoSize = True
        Me.chkHex.Location = New System.Drawing.Point(248, 55)
        Me.chkHex.Name = "chkHex"
        Me.chkHex.Size = New System.Drawing.Size(48, 16)
        Me.chkHex.TabIndex = 8
        Me.chkHex.Text = "HEX"
        Me.chkHex.UseVisualStyleBackColor = True
        '
        'chkDebug
        '
        Me.chkDebug.AutoSize = True
        Me.chkDebug.Location = New System.Drawing.Point(248, 32)
        Me.chkDebug.Name = "chkDebug"
        Me.chkDebug.Size = New System.Drawing.Size(89, 16)
        Me.chkDebug.TabIndex = 7
        Me.chkDebug.Text = "Debug Print"
        Me.chkDebug.UseVisualStyleBackColor = True
        '
        'chkReceiveDown
        '
        Me.chkReceiveDown.AutoSize = True
        Me.chkReceiveDown.Location = New System.Drawing.Point(15, 74)
        Me.chkReceiveDown.Name = "chkReceiveDown"
        Me.chkReceiveDown.Size = New System.Drawing.Size(48, 16)
        Me.chkReceiveDown.TabIndex = 4
        Me.chkReceiveDown.Text = "아래"
        Me.chkReceiveDown.UseVisualStyleBackColor = True
        '
        'chkReceiveUp
        '
        Me.chkReceiveUp.AutoSize = True
        Me.chkReceiveUp.Location = New System.Drawing.Point(15, 51)
        Me.chkReceiveUp.Name = "chkReceiveUp"
        Me.chkReceiveUp.Size = New System.Drawing.Size(36, 16)
        Me.chkReceiveUp.TabIndex = 3
        Me.chkReceiveUp.Text = "위"
        Me.chkReceiveUp.UseVisualStyleBackColor = True
        '
        'chkReceiveLeft
        '
        Me.chkReceiveLeft.AutoSize = True
        Me.chkReceiveLeft.Location = New System.Drawing.Point(15, 97)
        Me.chkReceiveLeft.Name = "chkReceiveLeft"
        Me.chkReceiveLeft.Size = New System.Drawing.Size(48, 16)
        Me.chkReceiveLeft.TabIndex = 5
        Me.chkReceiveLeft.Text = "왼쪽"
        Me.chkReceiveLeft.UseVisualStyleBackColor = True
        '
        'chkReceiveRight
        '
        Me.chkReceiveRight.AutoSize = True
        Me.chkReceiveRight.Location = New System.Drawing.Point(15, 120)
        Me.chkReceiveRight.Name = "chkReceiveRight"
        Me.chkReceiveRight.Size = New System.Drawing.Size(60, 16)
        Me.chkReceiveRight.TabIndex = 6
        Me.chkReceiveRight.Text = "오른쪽"
        Me.chkReceiveRight.UseVisualStyleBackColor = True
        '
        'txtDebug
        '
        Me.txtDebug.Location = New System.Drawing.Point(381, 6)
        Me.txtDebug.Multiline = True
        Me.txtDebug.Name = "txtDebug"
        Me.txtDebug.ScrollBars = System.Windows.Forms.ScrollBars.Vertical
        Me.txtDebug.Size = New System.Drawing.Size(336, 512)
        Me.txtDebug.TabIndex = 19
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.NumericUpDown4)
        Me.GroupBox1.Controls.Add(Me.NumericUpDown3)
        Me.GroupBox1.Controls.Add(Me.Button3)
        Me.GroupBox1.Controls.Add(Me.Button2)
        Me.GroupBox1.Controls.Add(Me.NumericUpDown2)
        Me.GroupBox1.Controls.Add(Me.Button1)
        Me.GroupBox1.Controls.Add(Me.cmbValue)
        Me.GroupBox1.Controls.Add(Me.Label2)
        Me.GroupBox1.Controls.Add(Me.Label1)
        Me.GroupBox1.Controls.Add(Me.nudsendlmstatus)
        Me.GroupBox1.Controls.Add(Me.nudEui4)
        Me.GroupBox1.Controls.Add(Me.nudEui3)
        Me.GroupBox1.Controls.Add(Me.nudEui2)
        Me.GroupBox1.Controls.Add(Me.nudEui1)
        Me.GroupBox1.Controls.Add(Me.chkSendEui)
        Me.GroupBox1.Controls.Add(Me.numSendRGB)
        Me.GroupBox1.Controls.Add(Me.chkSendDown)
        Me.GroupBox1.Controls.Add(Me.chkSendUp)
        Me.GroupBox1.Controls.Add(Me.butSend)
        Me.GroupBox1.Controls.Add(Me.chkSendLeft)
        Me.GroupBox1.Controls.Add(Me.chkSendRight)
        Me.GroupBox1.Location = New System.Drawing.Point(6, 6)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(359, 195)
        Me.GroupBox1.TabIndex = 17
        Me.GroupBox1.TabStop = False
        Me.GroupBox1.Text = "Send"
        '
        'Button2
        '
        Me.Button2.Location = New System.Drawing.Point(293, 116)
        Me.Button2.Name = "Button2"
        Me.Button2.Size = New System.Drawing.Size(43, 23)
        Me.Button2.TabIndex = 20
        Me.Button2.Text = "Button2"
        Me.Button2.UseVisualStyleBackColor = True
        '
        'NumericUpDown2
        '
        Me.NumericUpDown2.Location = New System.Drawing.Point(235, 116)
        Me.NumericUpDown2.Name = "NumericUpDown2"
        Me.NumericUpDown2.Size = New System.Drawing.Size(52, 21)
        Me.NumericUpDown2.TabIndex = 19
        '
        'Button1
        '
        Me.Button1.Location = New System.Drawing.Point(245, 140)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(90, 21)
        Me.Button1.TabIndex = 18
        Me.Button1.Text = "Send DAta"
        Me.Button1.UseVisualStyleBackColor = True
        '
        'cmbValue
        '
        Me.cmbValue.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cmbValue.FormattingEnabled = True
        Me.cmbValue.Items.AddRange(New Object() {"", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "더하기", "빼기", "곱하기", "나누기", "등호"})
        Me.cmbValue.Location = New System.Drawing.Point(142, 111)
        Me.cmbValue.Name = "cmbValue"
        Me.cmbValue.Size = New System.Drawing.Size(77, 20)
        Me.cmbValue.TabIndex = 17
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(97, 114)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(41, 12)
        Me.Label2.TabIndex = 16
        Me.Label2.Text = "Value:"
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(97, 87)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(44, 12)
        Me.Label1.TabIndex = 15
        Me.Label1.Text = "Status:"
        '
        'nudsendlmstatus
        '
        Me.nudsendlmstatus.Location = New System.Drawing.Point(142, 82)
        Me.nudsendlmstatus.Maximum = New Decimal(New Integer() {16, 0, 0, 0})
        Me.nudsendlmstatus.Name = "nudsendlmstatus"
        Me.nudsendlmstatus.Size = New System.Drawing.Size(77, 21)
        Me.nudsendlmstatus.TabIndex = 14
        '
        'nudEui4
        '
        Me.nudEui4.Hexadecimal = True
        Me.nudEui4.Location = New System.Drawing.Point(283, 21)
        Me.nudEui4.Maximum = New Decimal(New Integer() {65535, 0, 0, 0})
        Me.nudEui4.Name = "nudEui4"
        Me.nudEui4.Size = New System.Drawing.Size(52, 21)
        Me.nudEui4.TabIndex = 13
        Me.nudEui4.Value = New Decimal(New Integer() {30777, 0, 0, 0})
        '
        'nudEui3
        '
        Me.nudEui3.Hexadecimal = True
        Me.nudEui3.Location = New System.Drawing.Point(225, 21)
        Me.nudEui3.Maximum = New Decimal(New Integer() {65535, 0, 0, 0})
        Me.nudEui3.Name = "nudEui3"
        Me.nudEui3.Size = New System.Drawing.Size(52, 21)
        Me.nudEui3.TabIndex = 12
        Me.nudEui3.Value = New Decimal(New Integer() {186, 0, 0, 0})
        '
        'nudEui2
        '
        Me.nudEui2.Hexadecimal = True
        Me.nudEui2.Location = New System.Drawing.Point(167, 21)
        Me.nudEui2.Maximum = New Decimal(New Integer() {65535, 0, 0, 0})
        Me.nudEui2.Name = "nudEui2"
        Me.nudEui2.Size = New System.Drawing.Size(52, 21)
        Me.nudEui2.TabIndex = 11
        Me.nudEui2.Value = New Decimal(New Integer() {28416, 0, 0, 0})
        '
        'nudEui1
        '
        Me.nudEui1.Hexadecimal = True
        Me.nudEui1.Location = New System.Drawing.Point(109, 21)
        Me.nudEui1.Maximum = New Decimal(New Integer() {65535, 0, 0, 0})
        Me.nudEui1.Name = "nudEui1"
        Me.nudEui1.Size = New System.Drawing.Size(52, 21)
        Me.nudEui1.TabIndex = 10
        Me.nudEui1.Value = New Decimal(New Integer() {13, 0, 0, 0})
        '
        'chkSendEui
        '
        Me.chkSendEui.AutoSize = True
        Me.chkSendEui.Checked = True
        Me.chkSendEui.CheckState = System.Windows.Forms.CheckState.Checked
        Me.chkSendEui.Location = New System.Drawing.Point(22, 21)
        Me.chkSendEui.Name = "chkSendEui"
        Me.chkSendEui.Size = New System.Drawing.Size(75, 16)
        Me.chkSendEui.TabIndex = 9
        Me.chkSendEui.Text = "Send Eui"
        Me.chkSendEui.UseVisualStyleBackColor = True
        '
        'numSendRGB
        '
        Me.numSendRGB.Location = New System.Drawing.Point(21, 157)
        Me.numSendRGB.Name = "numSendRGB"
        Me.numSendRGB.Size = New System.Drawing.Size(112, 21)
        Me.numSendRGB.TabIndex = 8
        '
        'chkSendDown
        '
        Me.chkSendDown.AutoSize = True
        Me.chkSendDown.Location = New System.Drawing.Point(21, 87)
        Me.chkSendDown.Name = "chkSendDown"
        Me.chkSendDown.Size = New System.Drawing.Size(48, 16)
        Me.chkSendDown.TabIndex = 4
        Me.chkSendDown.Text = "아래"
        Me.chkSendDown.UseVisualStyleBackColor = True
        '
        'chkSendUp
        '
        Me.chkSendUp.AutoSize = True
        Me.chkSendUp.Location = New System.Drawing.Point(21, 64)
        Me.chkSendUp.Name = "chkSendUp"
        Me.chkSendUp.Size = New System.Drawing.Size(36, 16)
        Me.chkSendUp.TabIndex = 3
        Me.chkSendUp.Text = "위"
        Me.chkSendUp.UseVisualStyleBackColor = True
        '
        'butSend
        '
        Me.butSend.Location = New System.Drawing.Point(245, 64)
        Me.butSend.Name = "butSend"
        Me.butSend.Size = New System.Drawing.Size(92, 39)
        Me.butSend.TabIndex = 7
        Me.butSend.Text = "보내기"
        Me.butSend.UseVisualStyleBackColor = True
        '
        'chkSendLeft
        '
        Me.chkSendLeft.AutoSize = True
        Me.chkSendLeft.Location = New System.Drawing.Point(21, 110)
        Me.chkSendLeft.Name = "chkSendLeft"
        Me.chkSendLeft.Size = New System.Drawing.Size(48, 16)
        Me.chkSendLeft.TabIndex = 5
        Me.chkSendLeft.Text = "왼쪽"
        Me.chkSendLeft.UseVisualStyleBackColor = True
        '
        'chkSendRight
        '
        Me.chkSendRight.AutoSize = True
        Me.chkSendRight.Location = New System.Drawing.Point(21, 133)
        Me.chkSendRight.Name = "chkSendRight"
        Me.chkSendRight.Size = New System.Drawing.Size(60, 16)
        Me.chkSendRight.TabIndex = 6
        Me.chkSendRight.Text = "오른쪽"
        Me.chkSendRight.UseVisualStyleBackColor = True
        '
        'butClose
        '
        Me.butClose.Location = New System.Drawing.Point(349, 12)
        Me.butClose.Name = "butClose"
        Me.butClose.Size = New System.Drawing.Size(75, 23)
        Me.butClose.TabIndex = 19
        Me.butClose.Text = "Close"
        Me.butClose.UseVisualStyleBackColor = True
        '
        'TimerRestart
        '
        Me.TimerRestart.Interval = 3000
        '
        'txtAnswer
        '
        Me.txtAnswer.Location = New System.Drawing.Point(474, 13)
        Me.txtAnswer.Name = "txtAnswer"
        Me.txtAnswer.Size = New System.Drawing.Size(162, 21)
        Me.txtAnswer.TabIndex = 21
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(439, 16)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(29, 12)
        Me.Label3.TabIndex = 22
        Me.Label3.Text = "정답"
        '
        'TimerSendValue
        '
        Me.TimerSendValue.Interval = 30
        '
        'Button3
        '
        Me.Button3.Location = New System.Drawing.Point(245, 167)
        Me.Button3.Name = "Button3"
        Me.Button3.Size = New System.Drawing.Size(90, 21)
        Me.Button3.TabIndex = 21
        Me.Button3.Text = "Picture"
        Me.Button3.UseVisualStyleBackColor = True
        '
        'NumericUpDown3
        '
        Me.NumericUpDown3.Location = New System.Drawing.Point(129, 167)
        Me.NumericUpDown3.Name = "NumericUpDown3"
        Me.NumericUpDown3.Size = New System.Drawing.Size(52, 21)
        Me.NumericUpDown3.TabIndex = 22
        '
        'NumericUpDown4
        '
        Me.NumericUpDown4.Location = New System.Drawing.Point(187, 167)
        Me.NumericUpDown4.Name = "NumericUpDown4"
        Me.NumericUpDown4.Size = New System.Drawing.Size(52, 21)
        Me.NumericUpDown4.TabIndex = 23
        '
        'frmMain
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(7.0!, 12.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(1404, 849)
        Me.Controls.Add(Me.Label3)
        Me.Controls.Add(Me.txtAnswer)
        Me.Controls.Add(Me.butClose)
        Me.Controls.Add(Me.tabPage)
        Me.Controls.Add(Me.cmbBaudrate)
        Me.Controls.Add(Me.cmbPortname)
        Me.Controls.Add(Me.butOpen)
        Me.Name = "frmMain"
        Me.Text = "통신테스트 프로그램"
        Me.WindowState = System.Windows.Forms.FormWindowState.Maximized
        Me.tabPage.ResumeLayout(False)
        Me.TabPage1.ResumeLayout(False)
        CType(Me.picture, System.ComponentModel.ISupportInitialize).EndInit()
        Me.TabPage2.ResumeLayout(False)
        Me.TabPage2.PerformLayout()
        Me.GroupBox2.ResumeLayout(False)
        Me.GroupBox2.PerformLayout()
        CType(Me.NumericUpDown1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.GroupBox1.ResumeLayout(False)
        Me.GroupBox1.PerformLayout()
        CType(Me.NumericUpDown2, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.nudsendlmstatus, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.nudEui4, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.nudEui3, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.nudEui2, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.nudEui1, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.numSendRGB, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.NumericUpDown3, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.NumericUpDown4, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents SerialPort As System.IO.Ports.SerialPort
    Friend WithEvents Timer As System.Windows.Forms.Timer
    Friend WithEvents cmbBaudrate As System.Windows.Forms.ComboBox
    Friend WithEvents cmbPortname As System.Windows.Forms.ComboBox
    Friend WithEvents butOpen As System.Windows.Forms.Button
    Friend WithEvents tabPage As System.Windows.Forms.TabControl
    Friend WithEvents TabPage1 As System.Windows.Forms.TabPage
    Friend WithEvents TabPage2 As System.Windows.Forms.TabPage
    Public WithEvents GroupBox2 As System.Windows.Forms.GroupBox
    Friend WithEvents txtDebugStatus As System.Windows.Forms.TextBox
    Friend WithEvents NumericUpDown1 As System.Windows.Forms.NumericUpDown
    Friend WithEvents chkHex As System.Windows.Forms.CheckBox
    Friend WithEvents chkDebug As System.Windows.Forms.CheckBox
    Friend WithEvents chkReceiveDown As System.Windows.Forms.CheckBox
    Friend WithEvents chkReceiveUp As System.Windows.Forms.CheckBox
    Friend WithEvents chkReceiveLeft As System.Windows.Forms.CheckBox
    Friend WithEvents chkReceiveRight As System.Windows.Forms.CheckBox
    Public WithEvents txtDebug As System.Windows.Forms.TextBox
    Public WithEvents GroupBox1 As System.Windows.Forms.GroupBox
    Friend WithEvents numSendRGB As System.Windows.Forms.NumericUpDown
    Public WithEvents chkSendDown As System.Windows.Forms.CheckBox
    Public WithEvents chkSendUp As System.Windows.Forms.CheckBox
    Friend WithEvents butSend As System.Windows.Forms.Button
    Friend WithEvents chkSendLeft As System.Windows.Forms.CheckBox
    Friend WithEvents chkSendRight As System.Windows.Forms.CheckBox
    Friend WithEvents chkSendEui As System.Windows.Forms.CheckBox
    Friend WithEvents nudEui4 As System.Windows.Forms.NumericUpDown
    Friend WithEvents nudEui3 As System.Windows.Forms.NumericUpDown
    Friend WithEvents nudEui2 As System.Windows.Forms.NumericUpDown
    Friend WithEvents nudEui1 As System.Windows.Forms.NumericUpDown
    Public WithEvents txtDebugAscill As System.Windows.Forms.TextBox
    Friend WithEvents butClose As System.Windows.Forms.Button
    Friend WithEvents nudsendlmstatus As System.Windows.Forms.NumericUpDown
    Friend WithEvents butClear As System.Windows.Forms.Button
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents picture As System.Windows.Forms.PictureBox
    Friend WithEvents cmbValue As System.Windows.Forms.ComboBox
    Friend WithEvents TimerRestart As System.Windows.Forms.Timer
    Friend WithEvents txtAnswer As System.Windows.Forms.TextBox
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents TimerSendValue As System.Windows.Forms.Timer
    Friend WithEvents Button1 As System.Windows.Forms.Button
    Friend WithEvents Button2 As System.Windows.Forms.Button
    Friend WithEvents NumericUpDown2 As System.Windows.Forms.NumericUpDown
    Friend WithEvents Button3 As System.Windows.Forms.Button
    Friend WithEvents NumericUpDown4 As System.Windows.Forms.NumericUpDown
    Friend WithEvents NumericUpDown3 As System.Windows.Forms.NumericUpDown

End Class
