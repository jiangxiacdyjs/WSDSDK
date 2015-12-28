// PTZ20Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_demo.h"
#include "PTZ20Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPTZ20Dlg dialog


CPTZ20Dlg::CPTZ20Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPTZ20Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPTZ20Dlg)
	m_data1 = -1;
	m_data2 = -1;
	m_packet = _T("");
	//}}AFX_DATA_INIT
}


void CPTZ20Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPTZ20Dlg)
	DDX_Control(pDX, IDC_COMBO_CMD, m_cmbCMD);
	DDX_Text(pDX, IDC_EDIT_DATA1, m_data1);
	DDX_Text(pDX, IDC_EDIT_DATA2, m_data2);
	DDX_Text(pDX, IDC_EDIT_PACKET, m_packet);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPTZ20Dlg, CDialog)
	//{{AFX_MSG_MAP(CPTZ20Dlg)
	ON_BN_CLICKED(IDC_BUTTON_TEST, OnButtonTest)
	ON_BN_CLICKED(IDC_RADIO_AUTO, OnRadioAuto)
	ON_BN_CLICKED(IDC_RADIO_DARM, OnRadioDarm)
	ON_BN_CLICKED(IDC_RADIO_IDLE, OnRadioIdle)
	ON_BN_CLICKED(IDC_RADIO_INQ, OnRadioInq)
	ON_BN_CLICKED(IDC_RADIO_CMR, OnRadioCmr)
	ON_BN_CLICKED(IDC_RADIO_PATTERN, OnRadioPattern)
	ON_BN_CLICKED(IDC_RADIO_PRODUCE, OnRadioProduce)
	ON_BN_CLICKED(IDC_RADIO_REGION, OnRadioRegion)
	ON_BN_CLICKED(IDC_RADIO_SEQUENCE, OnRadioSequence)
	ON_BN_CLICKED(IDC_RADIO_SYS, OnRadioSys)
	ON_BN_CLICKED(IDC_RADIO_TITLE, OnRadioTitle)
	ON_BN_CLICKED(IDC_RADIO_VAR, OnRadioVar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPTZ20Dlg message handlers


void CPTZ20Dlg::OnButtonTest() 
{
    SetDlgItemText(IDC_EDIT_RESULT, "");
    UpdateData();

	if (m_cmbCMD.GetCurSel() < 0)
	{
		return;
	}

    NS_PTZ20_CMD_S cmd;
    ZeroMemory(&cmd, sizeof(NS_PTZ20_CMD_S));
    cmd.dwSize = sizeof(NS_PTZ20_CMD_S);
    cmd.data1 = -1;
    cmd.data2 = -1;

    int sel = m_cmbCMD.GetCurSel();
	if (((CButton *)GetDlgItem(IDC_RADIO_SEQUENCE))->GetCheck())//巡航扫描指令集
	{
		cmd.ptz20 = (NS_PTZ20_CMD_CODE_E)(NS_PTZ20_CMD_CODE_SEQUENCE_RUN + m_cmbCMD.GetCurSel());

        if (sel == 0)
        {
            cmd.data2 = m_data2;
        }
        else if (sel == 1)
        {
            cmd.data2 = m_data2;
        }
        else if (sel == 2)
        {
            cmd.data2 = m_data2;
        }
        else if (sel == 3)
        {
        }
        else
        {
            cmd.data1 = m_data1;
            cmd.data2 = m_data2;
        }
	}
    else if (((CButton *)GetDlgItem(IDC_RADIO_AUTO))->GetCheck())//左右扫描指令集
    {
        cmd.ptz20 = (NS_PTZ20_CMD_CODE_E)(NS_PTZ20_CMD_CODE_AUTO_PAN_RUN + m_cmbCMD.GetCurSel());

        if (sel == 6)
        {
            cmd.data1 = m_data1;
            cmd.data2 = m_data2;
        }
        else if (sel == 5)
        {
        }
        else
        {
            cmd.data2 = m_data2;
        }
    }
    else if (((CButton *)GetDlgItem(IDC_RADIO_PATTERN))->GetCheck())//花样扫描指令集
    {
        cmd.ptz20 = (NS_PTZ20_CMD_CODE_E)(NS_PTZ20_CMD_CODE_PATTERN_RUN + m_cmbCMD.GetCurSel());

        if (sel == 5)
        {
        }
        else
        {
            cmd.data2 = m_data2;
        }
    }
    else if (((CButton *)GetDlgItem(IDC_RADIO_IDLE))->GetCheck())//看守指令集
    {
        cmd.ptz20 = (NS_PTZ20_CMD_CODE_E)(NS_PTZ20_CMD_CODE_IDLE_OFF + m_cmbCMD.GetCurSel());

        if (sel == 0)
        {
        }
        else
        {
            cmd.data2 = m_data2;
        }
    }
    else if (((CButton *)GetDlgItem(IDC_RADIO_REGION))->GetCheck())//区域指示指令集
    {
        cmd.ptz20 = (NS_PTZ20_CMD_CODE_E)(NS_PTZ20_CMD_CODE_REGION_LEFT + m_cmbCMD.GetCurSel());

        if (sel == 3)
        {
        }
        else
        {
            cmd.data2 = m_data2;
        }
    }
    else if (((CButton *)GetDlgItem(IDC_RADIO_TITLE))->GetCheck())//标题指令集
    {
        cmd.ptz20 = (NS_PTZ20_CMD_CODE_E)(NS_PTZ20_CMD_CODE_TITLE_ALL_ENABLE1 + m_cmbCMD.GetCurSel());
        cmd.data2 = m_data2;
    }
    else if (((CButton *)GetDlgItem(IDC_RADIO_SYS))->GetCheck())//系统指令集
    {
        cmd.ptz20 = (NS_PTZ20_CMD_CODE_E)(NS_PTZ20_CMD_CODE_DATA_PROCESS + m_cmbCMD.GetCurSel());

        if (sel == 0)
        {
            cmd.data1 = m_data1;
        }
        else if (sel == 1)
        {
            cmd.data1 = m_data1;
        }
        else if (sel == 2)
        {
        }
        else if (sel == 24)
        {
            cmd.data1 = m_data1;
            cmd.data2 = m_data2;
        }
        else if (sel == 25)
        {
            cmd.data1 = m_data1;
            cmd.data2 = m_data2;
        }
        else if (sel == 26)
        {
        }
        else if (sel == 27)
        {
            cmd.data1 = m_data1;
            cmd.data2 = m_data2;
        }
        else
        {
            cmd.data2 = m_data2;
        }
    }
    else if (((CButton *)GetDlgItem(IDC_RADIO_DARM))->GetCheck())// 报警指令集
    {
        cmd.ptz20 = (NS_PTZ20_CMD_CODE_E)(NS_PTZ20_CMD_CODE_INQ_DARM_INPUT + m_cmbCMD.GetCurSel());

        if (sel == 0)
        {
        }
        else if (sel == 1)
        {
            cmd.data2 = m_data2;
        }
        else if (sel == 2)
        {
            cmd.data2 = m_data2;
        }
        else if (sel == 3)
        {
            cmd.data2 = m_data2;
        }
        else
        {
            cmd.data1 = m_data1;
            cmd.data2 = m_data2;
        }
    }
    else if (((CButton *)GetDlgItem(IDC_RADIO_INQ))->GetCheck())// 查询指令集
    {
        cmd.ptz20 = (NS_PTZ20_CMD_CODE_E)(NS_PTZ20_CMD_CODE_INQ_DOME_CONFIG + m_cmbCMD.GetCurSel());

        if (sel < 10)
        {
        }
        else if (sel > 19)
        {
        }
        else
        {
            cmd.data2 = m_data2;
        }
    }
    else if (((CButton *)GetDlgItem(IDC_RADIO_VAR))->GetCheck())// 变长指令集
    {
        cmd.ptz20 = (NS_PTZ20_CMD_CODE_E)(NS_PTZ20_CMD_CODE_SET_PAN_POS + m_cmbCMD.GetCurSel());

        ASSERT(m_packet.GetLength() < NS_PTZ_CMD_PACKET_LEN);
        strcpy(cmd.packet, m_packet);
    }
    else if (((CButton *)GetDlgItem(IDC_RADIO_CMR))->GetCheck())//摄像机指令集
    {
        cmd.ptz20 = (NS_PTZ20_CMD_CODE_E)(NS_PTZ20_CMD_CODE_CMR_DEFAULT + m_cmbCMD.GetCurSel());

        if (sel == 0)
        {
            cmd.data2 = m_data2;
        }
        else if (sel == 1)
        {
            cmd.data2 = m_data2;
        }
        else if (sel == 5)
        {
            cmd.data1 = m_data1;
        }
        else if (sel == 6)
        {
            cmd.data1 = m_data1;
        }
        else
        {
            cmd.data1 = m_data1;
            cmd.data2 = m_data2;
        }
    }
    else if (((CButton *)GetDlgItem(IDC_RADIO_PRODUCE))->GetCheck())// 生产指令集
    {
        cmd.ptz20 = (NS_PTZ20_CMD_CODE_E)(NS_PTZ20_CMD_CODE_PRO_IMPORTANCE_CMD + m_cmbCMD.GetCurSel());

        if (sel == 7)
        {
            cmd.data2 = m_data2;
        }
        else if (sel == 8)
        {
            cmd.data2 = m_data2;
        }
        else if (sel == 9)
        {
            cmd.data2 = m_data2;
        }
        else if (sel == 10)
        {
            cmd.data2 = m_data2;
        }
        else if (sel == 11)
        {
            cmd.data1 = m_data1;
            cmd.data2 = m_data2;
        }
        else
        {
        }
    }
    else
    {
        ASSERT(FALSE);
    }

	int ret = 0;
	if (g_u32DevHandle)
	{
		ret = NS_NET_PTZControl(g_u32DevHandle, NS_CMD_PTZ20, &cmd, cmd.dwSize);
		if (strlen(cmd.result) > 0)
		{
			SetDlgItemText(IDC_EDIT_RESULT, cmd.result);
		}
		else
		{
			AfxMessageBox("失败");
		}
	}
}



void CPTZ20Dlg::OnRadioSequence() 
{
	// TODO: Add your control notification handler code here
    SetDlgItemText(IDC_EDIT_HELP,
    "运行巡航扫描（m）-data2 m	m:sequenceNO(0-7)\r\n"
    "停止巡航扫描（m）-data2 m	m:sequenceNO(0-7)\r\n"
    "删除巡航扫描（m）-data2 m	m:sequenceNO(0-7)\r\n"
    "清空巡航标题	  无参数	\r\n"
    "插入巡航预置位	  -data1 n -data2 m  n:presetNO(1-255) m:sequenceNO(0-7)\r\n"
    "移除巡航预置位	  -data1 n -data2 m  n:presetNO(1-255) m:sequenceNO(0-7)\r\n"
    "驻留时间         -data1 x -data2 m  x:time(1-255) m:sequenceNO(0-7)\r\n"
    "巡航预置位速度	  -data1 x -data2 m  x:speed(1-255) m:sequenceNO(0-7)\r\n");
  
    m_cmbCMD.ResetContent();
	m_cmbCMD.AddString("运行巡航扫描");
	m_cmbCMD.AddString("停止巡航扫描");
	m_cmbCMD.AddString("删除巡航扫描");
	m_cmbCMD.AddString("清空巡航标题");
	m_cmbCMD.AddString("插入巡航预置位");
	m_cmbCMD.AddString("移除巡航预置位");
	m_cmbCMD.AddString("驻留时间");
	m_cmbCMD.AddString("巡航预置位速度");
}

void CPTZ20Dlg::OnRadioAuto() 
{
    // TODO: Add your control notification handler code here
    SetDlgItemText(IDC_EDIT_HELP,
        "运行左右扫描（m）   -data2 m	m:autopanNO(0-7)\r\n"
        "停止左右扫描（m）   -data2 m	m:autopanNO(0-7)\r\n"
        "删除左右扫描（m）   -data2 m	m:autopanNO(0-7)\r\n"
        "设左限位	         -data2 m	m:autopanNO(0-7)\r\n"
        "设右限位	         -data2 m 	m:autopanNO(0-7)\r\n"
        "清空左右扫描标题    无参数\r\n"
        "设扫描速度          -data1 x -data2 m  x:speed(1-255) m:autopanNO(0-7)\r\n"
        );

    m_cmbCMD.ResetContent();
    m_cmbCMD.AddString("运行左右扫描");
    m_cmbCMD.AddString("停止左右扫描");
    m_cmbCMD.AddString("删除左右扫描");
    m_cmbCMD.AddString("设左限位");
    m_cmbCMD.AddString("设右限位");
    m_cmbCMD.AddString("清空左右扫描标题");
    m_cmbCMD.AddString("设扫描速度");
}

void CPTZ20Dlg::OnRadioPattern() 
{
    // TODO: Add your control notification handler code here
    SetDlgItemText(IDC_EDIT_HELP,
        "运行花样扫描（m）	 -data2 m	m:patternNO(0-7)\r\n"
        "停止花样扫描（m）	 -data2 m	m:patternNO(0-7)\r\n"
        "删除花样扫描（m）	 -data2 m	m:patternNO(0-7)\r\n"
        "录制花样扫描        -data2 m	m:patternNO(0-7)\r\n"
        "停止录制花样扫描    -data2 m 	m:patternNO(0-7)\r\n"
        "清空花样扫描标题	 无参数\r\n"
        );

    m_cmbCMD.ResetContent();
    m_cmbCMD.AddString("运行花样扫描");
    m_cmbCMD.AddString("停止花样扫描");
    m_cmbCMD.AddString("删除花样扫描");
    m_cmbCMD.AddString("录制花样扫描");
    m_cmbCMD.AddString("停止录制花样扫描");
    m_cmbCMD.AddString("清空花样扫描标题");
}

void CPTZ20Dlg::OnRadioIdle() 
{
    // TODO: Add your control notification handler code here
    SetDlgItemText(IDC_EDIT_HELP,
        "关看守功能（m）     无参数\r\n"
        "设看守巡航扫描（m） -data2 m	m:sequenceNO(0-7)\r\n"
        "设看守花样扫描（m） -data2 m	m:patternNO(0-7)\r\n"
        "设看守左右扫描      -data2 m	m:autopanNO(0-7)\r\n"
        "设看守预置位        -data2 m 	m:presetNO(0-7)\r\n"
        "设空闲时间          -data2 m 	m:time(2-255)\r\n"
        );

    m_cmbCMD.ResetContent();
    m_cmbCMD.AddString("关看守功能");
    m_cmbCMD.AddString("设看守巡航扫描");
    m_cmbCMD.AddString("设看守花样扫描");
    m_cmbCMD.AddString("设看守左右扫描");
    m_cmbCMD.AddString("设看守预置位");
    m_cmbCMD.AddString("设空闲时间");
}

void CPTZ20Dlg::OnRadioRegion() 
{
    SetDlgItemText(IDC_EDIT_HELP,
        "设区域指示左限位（m） -data2 m	m:RegionNO(0-7)\r\n"
        "设区域指示右限位（m） -data2 m	m:RegionNO(0-7)\r\n"
        "删除区域指示          -data2 m	m:RegionNO(0-7)\r\n"
        "清空区域标题（m）     无参数\r\n"
        );

    m_cmbCMD.ResetContent();
    m_cmbCMD.AddString("设区域指示左限位");
    m_cmbCMD.AddString("设区域指示右限位");
    m_cmbCMD.AddString("删除区域指示");
    m_cmbCMD.AddString("清空区域标题");
}

void CPTZ20Dlg::OnRadioTitle() 
{
    SetDlgItemText(IDC_EDIT_HELP,
        "全部标题标志开关 -data2 x	x: 0/1=关/开\r\n"
        "全部标题开关     -data2 x	x: 0/1=关/开\r\n"
        "球机标题开关     -data2 x	x: 0/1=关/开\r\n"
        "预置位标题开关   -data2 x	x:(0-7) 0/1=关/开      2~7 不同模式\r\n"
        "自动扫描标题开关 -data2 x	x:(0-7) 0/1=关/开      2~7 不同模式\r\n"
        "巡航扫描标题开关 -data2 x	x:(0-7) 0/1=关/开      2~7 不同模式\r\n"
        "花样扫描标题开关 -data2 x	x:(0-7) 0/1=关/开      2~7 不同模式\r\n"
        "区域指示标志开关 -data2 x	x:(0-7) 0/1=关/开      2~7 不同模式\r\n"
        "方向指示标志开关 -data2 x	x:(0-7) 0/1=关/开      2~7 不同模式\r\n"
        "倍数指示标志开关 -data2 x	x:(0-7) 0/1=关/开      2~7 不同模式\r\n"
        "温度指示标志开关 -data2 x	x: 0/1=关/开\r\n"
        "电压指示标志开关 -data2 x	x: 0/1=关/开\r\n"
        "系统时间显示开关 -data2 x	x: 0/1=关/开\r\n"
        "系统日期显示开关 -data2 x	x: 0/1=关/开\r\n"
        "照度指示标志开关 -data2 x	x: 0/1=关/开\r\n"
        "报警指示标志开关 -data2 x	x: 0/1=关/开\r\n"
        );

    m_cmbCMD.ResetContent();
    m_cmbCMD.AddString("全部标题标志开关");
    m_cmbCMD.AddString("全部标题开关");
    m_cmbCMD.AddString("球机标题开关");
    m_cmbCMD.AddString("预置位标题开关");
    m_cmbCMD.AddString("自动扫描标题开关");
    m_cmbCMD.AddString("巡航扫描标题开关");
    m_cmbCMD.AddString("花样扫描标题开关");
    m_cmbCMD.AddString("区域指示标志开关");
    m_cmbCMD.AddString("方向指示标志开关");
    m_cmbCMD.AddString("倍数指示标志开关");
    m_cmbCMD.AddString("温度指示标志开关");
    m_cmbCMD.AddString("电压指示标志开关");
    m_cmbCMD.AddString("系统时间显示开关");
    m_cmbCMD.AddString("系统日期显示开关");
    m_cmbCMD.AddString("照度指示标志开关");
    m_cmbCMD.AddString("报警指示标志开关");
}

void CPTZ20Dlg::OnRadioSys() 
{
    SetDlgItemText(IDC_EDIT_HELP,
        "数据处理         -data1 x x:（0~8）， \r\n"
        "                     0：系统软启动 \r\n"
        "                     1：系统默认值 \r\n"
        "                     2：删除预置位数据 \r\n"
        "                     3：删除左右扫描数据 \r\n"
        "                     4：删除巡航扫描数据 \r\n"
        "                     5：删除模式扫描数据 \r\n"
        "                     6：删除区域标题数据 \r\n"
        "                     7：删除隐私保护数据 \r\n"
        "                     8：删除球机标题 \r\n"
        "球机位置功能     -data1 x x:（0~2），0:设正北方向 1:水平翻转  2：云台原点\r\n"
        "屏幕信息清屏     -data2 x X:(0~1)  0:室外模式  1：室内模式\r\n"
        "红外亮度室内模式 -data2 x X:(0~3)  0:红外控制自动模式  1:红外控制近灯模式   2:红外控制中灯模式    3:红外控制远灯模式\r\n"
        "红外控制模式     -data2 x x:(0-3)模式  0:开  1：聚焦　　2：光圈    3：关\r\n"
        "遥杆自动恢复模式 -data2 x x:(0-255)\r\n"
        "自动聚焦恢复时间 -data2 x x:(0-255)\r\n"
        "自动光圈恢复时间 -data2 x x:(0-255)\r\n"
        "OSD字符颜色      -data2 x x:(0-8)\r\n"
        "OSD水平位置      -data2 x x:(0-7)\r\n"
        "OSD垂直位置      -data2 x x:(0-63)\r\n"
        "照度检测模式     -data2 x x:(0-1)\r\n"
        "开灯照度阀值     -data2 x x:(0-10)\r\n"
        "云台菜单         -data2 x x:(0-1)\r\n"
        "摄像机菜单       -data2 x x:(0-1)\r\n"
        "垂直运动范围     -data2 x x:(0-10)\r\n"
        "水平手动速度等级 -data2 x x:(0-9)\r\n"
        "垂直运动范围     -data2 x x:(0-9)\r\n"
        "温度单位         -data2 x x:(0-1)\r\n"
        "变焦转速联动     -data2 x x:0关  1 开\r\n"
        "雨刷控制         -data2 x x:0关  1 开\r\n"
        "风扇控制         -data2 x x:(0-7) 关/开    30/35/40/45/50/55\r\n"
        "加热控制         -data2 x x:(0-7) 关/开    5/0/-5/-10/-15/-20\r\n"
        "屏幕信息清行     -data2 x x:(0-12)\r\n"
        "设转彩色时间     -data1 h -data2 m H:小时（0~23）  M;分钟(0~59)\r\n"
        "设转黑白时间     -data1 h -data2 m H:小时（0~23）  M;分钟(0~59)\r\n"
        "云台自动重启关   无参数\r\n"
        "云台自动重启开   -data1 h -data2 m H:小时（0~23）  M;分钟(0~59)\r\n"
        "初始化信息保留   -data2 T T:时间（0~255）   0：初始化信息\r\n"
        );

    m_cmbCMD.ResetContent();
    m_cmbCMD.AddString("数据处理");
    m_cmbCMD.AddString("球机位置功能");
    m_cmbCMD.AddString("屏幕信息清屏");
    m_cmbCMD.AddString("红外亮度室内模式");
    m_cmbCMD.AddString("红外控制模式");
    m_cmbCMD.AddString("遥杆自动恢复模式");
    m_cmbCMD.AddString("自动聚焦恢复时间");
    m_cmbCMD.AddString("自动光圈恢复时间");
    m_cmbCMD.AddString("OSD字符颜色");
    m_cmbCMD.AddString("OSD水平位置");
    m_cmbCMD.AddString("OSD垂直位置");
    m_cmbCMD.AddString("照度检测模式");
    m_cmbCMD.AddString("开灯照度阀值");
    m_cmbCMD.AddString("云台菜单");
    m_cmbCMD.AddString("摄像机菜单");
    m_cmbCMD.AddString("垂直运动范围");
    m_cmbCMD.AddString("水平手动速度等级");
    m_cmbCMD.AddString("垂直运动范围");
    m_cmbCMD.AddString("温度单位");
    m_cmbCMD.AddString("变焦转速联动");
    m_cmbCMD.AddString("雨刷控制");
    m_cmbCMD.AddString("风扇控制");
    m_cmbCMD.AddString("加热控制");
    m_cmbCMD.AddString("屏幕信息清行");
    m_cmbCMD.AddString("设转彩色时间");
    m_cmbCMD.AddString("设转黑白时间");
    m_cmbCMD.AddString("云台自动重启关");
    m_cmbCMD.AddString("云台自动重启开");
    m_cmbCMD.AddString("初始化信息保留");
}

void CPTZ20Dlg::OnRadioDarm() 
{
    // TODO: Add your control notification handler code here
    SetDlgItemText(IDC_EDIT_HELP,
        "查询报警输入状态（m）无参数\r\n"
        "返回报警输入状（m）  -data2 m	m: 0：断开1：闭合\r\n"
        "报警输出驱动         -data2 m	m: 0：断开1：闭合\r\n"
        "报警上传模式（m）    -data2 m	m: 0:报警请求上传模式\r\n"
        "                                  1:自动连续上传模式，每秒一次\r\n"
        "                                  2:自动变化上传模式，报警输入状态发送变化时，上次数据\r\n"
        );

    m_cmbCMD.ResetContent();
    m_cmbCMD.AddString("查询报警输入状态");
    m_cmbCMD.AddString("返回报警输入状");
    m_cmbCMD.AddString("报警输出驱动");
    m_cmbCMD.AddString("报警上传模式");
}

void CPTZ20Dlg::OnRadioInq() 
{
    SetDlgItemText(IDC_EDIT_HELP,
        "请求设备配置                无参数\r\n"
        "请求设备运行状态            无参数\r\n"
        "请求水平位置                无参数\r\n"
        "请求云台位置                无参数\r\n"
        "请求球机位置                无参数\r\n"
        "请求设备系列号              无参数\r\n"
        "请求设备型号                无参数\r\n"
        "请求摄像机型号              无参数\r\n"
        "请求球机软件版本号          无参数\r\n"
        "请求时钟                    无参数\r\n"

        "请求机相温度               -data2 x X:0~3\r\n"
        "请求设备电压               -data2 x X:0~3\r\n"
        "请求风扇速度               -data2 x X:0~3\r\n"
        "请求光敏电压               -data2 x X:0~3\r\n"
        "请求球机标题               -data2 x X:0~3\r\n"
        "请求预置位标题             -data2 x X:1~255\r\n"
        "请求左右扫描标题           -data2 x X:0~7\r\n"
        "请求巡视扫描标题           -data2 x X:0~7\r\n"
        "请求花样扫描标题           -data2 x X:0~7\r\n"
        "请求区域指示标题           -data2 x X:0~7\r\n"
        "请求摄像机软件版本         无参数\r\n"
        );

    m_cmbCMD.ResetContent();
    m_cmbCMD.AddString("请求设备配置");
    m_cmbCMD.AddString("请求设备运行状态");
    m_cmbCMD.AddString("请求水平位置");
    m_cmbCMD.AddString("请求云台位置");
    m_cmbCMD.AddString("请求球机位置");
    m_cmbCMD.AddString("请求设备系列号");
    m_cmbCMD.AddString("请求设备型号");
    m_cmbCMD.AddString("请求摄像机型号");
    m_cmbCMD.AddString("请求球机软件版本号");
    m_cmbCMD.AddString("请求时钟");

    m_cmbCMD.AddString("请求机相温度");
    m_cmbCMD.AddString("请求设备电压");
    m_cmbCMD.AddString("请求风扇速度");
    m_cmbCMD.AddString("请求光敏电压");
    m_cmbCMD.AddString("请求球机标题");
    m_cmbCMD.AddString("请求预置位标题");
    m_cmbCMD.AddString("请求左右扫描标题");
    m_cmbCMD.AddString("请求巡视扫描标题");
    m_cmbCMD.AddString("请求花样扫描标题");
    m_cmbCMD.AddString("请求区域指示标题");
    m_cmbCMD.AddString("请求摄像机软件版本");
}

void CPTZ20Dlg::OnRadioVar() 
{
    SetDlgItemText(IDC_EDIT_HELP,
        "设置水平位置       -packet d-d-d\r\n"
        "设置云台位置       -packet d-d-d-d-d\r\n"
        "设置球机位置       -packet d-d-d-d-d-d-d\r\n"
        "设置设备系列号     -packet string  \r\n"
        "设置时钟           -packet Y-M-D-W-h-m-s\r\n"
        "设置球机标题       -packet string\r\n"
        "设置预置位标题     -packet ID-string  预置位ID(1-255)-string\r\n"
        "设置左右扫描标题   -packet ID-string  扫描ID(0~7)-string \r\n"
        "设置巡视扫描标题   -packet ID-string  扫描ID(0~7)-string \r\n"
        "设置花样扫描标题   -packet ID-string  扫描ID(0~7)-string \r\n"
        "设置区域指示标题   -packet ID-string  区域指示标(0~7)--string \r\n"
        "设置隐私区域       -packet ID-W-H 区域号（0-23）W :区域宽（1-80） H ：区域高（1-60）\r\n"
        "三维智能定位1      -packet Xs-Ys-Xe-Ye Xs(0-255)起点坐标x Ys(0-255)起点坐标y    Xe(0-255）终点坐标x    Ye(0-255)终点坐标y\r\n"
        "三维智能定位2      -packet Xs-Ys-Xe-Ye Xs(0-255)起点坐标x Ys(0-255)起点坐标y    Xe(0-255）终点坐标x    Ye(0-255)终点坐标y \r\n"
        "三维智能定位3      -packet Xs-Ys-Xe-Ye Xs(0-255)起点坐标x Ys(0-255)起点坐标y    Xe(0-255）终点坐标x    Ye(0-255)终点坐标y \r\n"
        "报警设置           -packet B1-B2-B3-B4-B5-B6-B7-B8-B9-B10-B11-B12\r\n"
        "                           B1:  报警通道号0-7 \r\n"
        "                           B2:  布防模式  0 手动布防，1自动布防。\r\n"
        "                           B3： 布防状态  1：布防 0： 撤防 \r\n"
        "                           B4： 输入状态  0  常开有效  1 常闭有效 \r\n"
        "                           B5： 功能类别  0: 巡航扫描 1 模式扫描  2 左右扫描  3预置位 \r\n"
        "                           B6： 功能ID 巡航（0-7） \r\n"
        "                                模式扫描（0-7）， 左右扫描（0-7）， 预置位（1-255） \r\n"
        "                           B7： 输出方式：0断开，1闭合 \r\n"
        "                           B8： 延迟时间 1—255 默认20 \r\n"
        "                           B9： 布防时间 H 时 \r\n"
        "                           B10：布防时间 M 分 \r\n"
        "                           B11：撤防时间 H 时 \r\n"
        "                           B12: 撤防时间 M 分 \r\n"
        "显示屏幕信息       -packet B1-B2-B3-B4-string "
        "                           B1：列坐标0-39  \r\n"
        "                           B2：行坐标0-12  \r\n"
        "                           B3：字符号显示属性0-3 全透， 全透+闪烁， 半透， 半透+闪烁\r\n"
        "                           B4：字符颜色  0-7  白色，红色，橙色， 黄色，绿色，青色， 蓝色， 紫色。\r\n"
        "设置设备品牌       -packet string String:需要设置的品牌字符串\r\n"
        );

    m_cmbCMD.ResetContent();
    m_cmbCMD.AddString("设置水平位置");
    m_cmbCMD.AddString("设置云台位置");
    m_cmbCMD.AddString("设置球机位置");
    m_cmbCMD.AddString("设置设备系列号");
    m_cmbCMD.AddString("设置时钟");
    m_cmbCMD.AddString("设置球机标题");
    m_cmbCMD.AddString("设置预置位标题");
    m_cmbCMD.AddString("设置左右扫描标题");
    m_cmbCMD.AddString("设置巡视扫描标题");
    m_cmbCMD.AddString("设置花样扫描标题");

    m_cmbCMD.AddString("设置区域指示标题");
    m_cmbCMD.AddString("设置隐私区域");
    m_cmbCMD.AddString("三维智能定位1");
    m_cmbCMD.AddString("三维智能定位2");
    m_cmbCMD.AddString("三维智能定位3");
    m_cmbCMD.AddString("报警设置");
    m_cmbCMD.AddString("显示屏幕信息");
    m_cmbCMD.AddString("设置设备品牌");
}

void CPTZ20Dlg::OnRadioCmr() 
{
    // TODO: Add your control notification handler code here
    SetDlgItemText(IDC_EDIT_HELP,
        "恢复摄像机默认值  -data2  x x(0~1)		0:按球机整体要求，恢复摄像机全部参数默认值 1：恢复亮度，对比度，色饱和度，锐度，AGC限值等参数默认值\r\n"
        "摄像机上电复位    -data2  x x:(0~1)	0:摄像机上电复位 1:摄像机软件复位\r\n"
        "AE模式            -data1 x -data2 v x:(0~4)模式	0:AE自动模式 1:AE快门优先模式	2:AE光圈优先模式 3:AE增益优先模式	4:AE亮度优先模式   v:(0~31)模式值\r\n"
        "BLC项块           -data1 x -data2 v x:(0~2)模式	0:BLC关闭	1:BLC模式	2:WDR模式  v:(0~255)范围值\r\n"
        "白平衡模式        -data1 x  -data2 v \r\n"
        "                      注意：x为不同值时，v有不同含义 \r\n"
        "                            x=0 白平衡模式,v：（0~5）自动、手动、跟踪、室内、室外、锁定 \r\n"
        "                            x=1 R增益         v:(0~255) \r\n"
        "                            x=2 B 增益        v:(0~255) \r\n"
        "                            x=3 自动光圈ALC   v:(0~255) \r\n"
        "                            x=4 自动光圈PLC   v:(0~255) \r\n"
        "                            x=5 数字变焦      v:(0-12) ，0为关 \r\n"
        "                            x=6 电子慢快门    v:(0-12) ，0为关 \r\n"
        "                            x=7 AGC限值       v:(0~255) \r\n"
        "                            x=8  图像亮度     v:(0~255) \r\n"
        "                            x=9  图像对比度   v:(0~255) \r\n"
        "                            x=10 图像色饱和度 v:(0~255) \r\n"
        "                            x=11 图像锐度     v:(0~255) \r\n"
        "                            x=12 变焦速度     v:(0~255) \r\n"
        "                            x=13 聚焦速度     v:(0~7) \r\n"
        "                            x=14 最小聚焦距离 v:(0~7) \r\n"
        "                            x=15 图像降噪DNR  v:(0-15) \r\n"
        "                            x=16 黑彩转换     v:(0-3)A/D/N/T \r\n"
        "                            x=17 图像冻结     v:0 关，1 开 \r\n"
        "                            x=18 图像水平镜像 v:0 关，1 开 \r\n"
        "                            x=19 图像垂直镜像 v:0 关，1 开 \r\n"
        "                            x=20 图像负片     v:0 关，1 开 \r\n"
        "                            x=21 图像稳定     v:0 关，1 开 \r\n"

        "图像水平位置  -data1 x x:(0-1920)\r\n"
        "图像垂直位置  -data1 x x:(0-1080)\r\n"
        "隐私区域功能  -data1 x -data2 m x:(0-23) 区域ID m:(0~2)  0:显示隐私区域  1:隐藏隐私区域  2:删除隐私区域\r\n"
        "设置隐私区域颜色  -data1 x -data2 c x:(0-23) C:(0-8)颜色\r\n"
        );

    m_cmbCMD.ResetContent();
    m_cmbCMD.AddString("恢复摄像机默认值");
    m_cmbCMD.AddString("摄像机上电复位");
    m_cmbCMD.AddString("AE模式");
    m_cmbCMD.AddString("BLC项块");
    m_cmbCMD.AddString("白平衡模式");
    m_cmbCMD.AddString("图像水平位置");
    m_cmbCMD.AddString("图像垂直位置");
    m_cmbCMD.AddString("隐私区域功能");
    m_cmbCMD.AddString("设置隐私区域颜色");
}

void CPTZ20Dlg::OnRadioProduce() 
{
    // TODO: Add your control notification handler code here
    SetDlgItemText(IDC_EDIT_HELP,
        "重要指令*        无参数 \r\n"
        "清除内存*        无参数 \r\n"
        "出厂设置*        无参数 \r\n"
        "默认设置*        无参数 \r\n"
        "硬件测试*        无参数 \r\n"
        "老化测试*        无参数 \r\n"
        "初始化标题*      无参数   \r\n"
        "设置摄像机型号*  -data2 x  分段管理  \r\n"
        "设置球机地址*    -data2 x  x:(1-255) \r\n"
        "雨刷位置调整*    -data2 x  x:(0-20) \r\n"
        "垂直位置调整*    -data2 x  x:(0-20) \r\n"
        "设置菜单语言*    -data1 e -data2 d e:(b7-b0)语言种类,按位处理，1为有效  d：(b7-b0)当前语言，,按位处理，1为有效，只能选一种语言  \r\n"
        "停止硬件测试     无参数    \r\n"
        "停止老化测试     无参数    \r\n"
        "获取老化测试报告 无参数        \r\n"
        );

    m_cmbCMD.ResetContent();
    m_cmbCMD.AddString("重要指令*");
    m_cmbCMD.AddString("清除内存*");
    m_cmbCMD.AddString("出厂设置*");
    m_cmbCMD.AddString("默认设置*");
    m_cmbCMD.AddString("硬件测试*");
    m_cmbCMD.AddString("老化测试*");
    m_cmbCMD.AddString("初始化标题*");
    m_cmbCMD.AddString("设置摄像机型号*");
    m_cmbCMD.AddString("设置球机地址*");
    m_cmbCMD.AddString("雨刷位置调整*");
    m_cmbCMD.AddString("垂直位置调整*");
    m_cmbCMD.AddString("设置菜单语言*");
    m_cmbCMD.AddString("停止硬件测试");
    m_cmbCMD.AddString("停止老化测试");
    m_cmbCMD.AddString("获取老化测试报告");
}
