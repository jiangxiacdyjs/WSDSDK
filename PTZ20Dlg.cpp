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
	if (((CButton *)GetDlgItem(IDC_RADIO_SEQUENCE))->GetCheck())//Ѳ��ɨ��ָ�
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
    else if (((CButton *)GetDlgItem(IDC_RADIO_AUTO))->GetCheck())//����ɨ��ָ�
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
    else if (((CButton *)GetDlgItem(IDC_RADIO_PATTERN))->GetCheck())//����ɨ��ָ�
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
    else if (((CButton *)GetDlgItem(IDC_RADIO_IDLE))->GetCheck())//����ָ�
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
    else if (((CButton *)GetDlgItem(IDC_RADIO_REGION))->GetCheck())//����ָʾָ�
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
    else if (((CButton *)GetDlgItem(IDC_RADIO_TITLE))->GetCheck())//����ָ�
    {
        cmd.ptz20 = (NS_PTZ20_CMD_CODE_E)(NS_PTZ20_CMD_CODE_TITLE_ALL_ENABLE1 + m_cmbCMD.GetCurSel());
        cmd.data2 = m_data2;
    }
    else if (((CButton *)GetDlgItem(IDC_RADIO_SYS))->GetCheck())//ϵͳָ�
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
    else if (((CButton *)GetDlgItem(IDC_RADIO_DARM))->GetCheck())// ����ָ�
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
    else if (((CButton *)GetDlgItem(IDC_RADIO_INQ))->GetCheck())// ��ѯָ�
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
    else if (((CButton *)GetDlgItem(IDC_RADIO_VAR))->GetCheck())// �䳤ָ�
    {
        cmd.ptz20 = (NS_PTZ20_CMD_CODE_E)(NS_PTZ20_CMD_CODE_SET_PAN_POS + m_cmbCMD.GetCurSel());

        ASSERT(m_packet.GetLength() < NS_PTZ_CMD_PACKET_LEN);
        strcpy(cmd.packet, m_packet);
    }
    else if (((CButton *)GetDlgItem(IDC_RADIO_CMR))->GetCheck())//�����ָ�
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
    else if (((CButton *)GetDlgItem(IDC_RADIO_PRODUCE))->GetCheck())// ����ָ�
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
			AfxMessageBox("ʧ��");
		}
	}
}



void CPTZ20Dlg::OnRadioSequence() 
{
	// TODO: Add your control notification handler code here
    SetDlgItemText(IDC_EDIT_HELP,
    "����Ѳ��ɨ�裨m��-data2 m	m:sequenceNO(0-7)\r\n"
    "ֹͣѲ��ɨ�裨m��-data2 m	m:sequenceNO(0-7)\r\n"
    "ɾ��Ѳ��ɨ�裨m��-data2 m	m:sequenceNO(0-7)\r\n"
    "���Ѳ������	  �޲���	\r\n"
    "����Ѳ��Ԥ��λ	  -data1 n -data2 m  n:presetNO(1-255) m:sequenceNO(0-7)\r\n"
    "�Ƴ�Ѳ��Ԥ��λ	  -data1 n -data2 m  n:presetNO(1-255) m:sequenceNO(0-7)\r\n"
    "פ��ʱ��         -data1 x -data2 m  x:time(1-255) m:sequenceNO(0-7)\r\n"
    "Ѳ��Ԥ��λ�ٶ�	  -data1 x -data2 m  x:speed(1-255) m:sequenceNO(0-7)\r\n");
  
    m_cmbCMD.ResetContent();
	m_cmbCMD.AddString("����Ѳ��ɨ��");
	m_cmbCMD.AddString("ֹͣѲ��ɨ��");
	m_cmbCMD.AddString("ɾ��Ѳ��ɨ��");
	m_cmbCMD.AddString("���Ѳ������");
	m_cmbCMD.AddString("����Ѳ��Ԥ��λ");
	m_cmbCMD.AddString("�Ƴ�Ѳ��Ԥ��λ");
	m_cmbCMD.AddString("פ��ʱ��");
	m_cmbCMD.AddString("Ѳ��Ԥ��λ�ٶ�");
}

void CPTZ20Dlg::OnRadioAuto() 
{
    // TODO: Add your control notification handler code here
    SetDlgItemText(IDC_EDIT_HELP,
        "��������ɨ�裨m��   -data2 m	m:autopanNO(0-7)\r\n"
        "ֹͣ����ɨ�裨m��   -data2 m	m:autopanNO(0-7)\r\n"
        "ɾ������ɨ�裨m��   -data2 m	m:autopanNO(0-7)\r\n"
        "������λ	         -data2 m	m:autopanNO(0-7)\r\n"
        "������λ	         -data2 m 	m:autopanNO(0-7)\r\n"
        "�������ɨ�����    �޲���\r\n"
        "��ɨ���ٶ�          -data1 x -data2 m  x:speed(1-255) m:autopanNO(0-7)\r\n"
        );

    m_cmbCMD.ResetContent();
    m_cmbCMD.AddString("��������ɨ��");
    m_cmbCMD.AddString("ֹͣ����ɨ��");
    m_cmbCMD.AddString("ɾ������ɨ��");
    m_cmbCMD.AddString("������λ");
    m_cmbCMD.AddString("������λ");
    m_cmbCMD.AddString("�������ɨ�����");
    m_cmbCMD.AddString("��ɨ���ٶ�");
}

void CPTZ20Dlg::OnRadioPattern() 
{
    // TODO: Add your control notification handler code here
    SetDlgItemText(IDC_EDIT_HELP,
        "���л���ɨ�裨m��	 -data2 m	m:patternNO(0-7)\r\n"
        "ֹͣ����ɨ�裨m��	 -data2 m	m:patternNO(0-7)\r\n"
        "ɾ������ɨ�裨m��	 -data2 m	m:patternNO(0-7)\r\n"
        "¼�ƻ���ɨ��        -data2 m	m:patternNO(0-7)\r\n"
        "ֹͣ¼�ƻ���ɨ��    -data2 m 	m:patternNO(0-7)\r\n"
        "��ջ���ɨ�����	 �޲���\r\n"
        );

    m_cmbCMD.ResetContent();
    m_cmbCMD.AddString("���л���ɨ��");
    m_cmbCMD.AddString("ֹͣ����ɨ��");
    m_cmbCMD.AddString("ɾ������ɨ��");
    m_cmbCMD.AddString("¼�ƻ���ɨ��");
    m_cmbCMD.AddString("ֹͣ¼�ƻ���ɨ��");
    m_cmbCMD.AddString("��ջ���ɨ�����");
}

void CPTZ20Dlg::OnRadioIdle() 
{
    // TODO: Add your control notification handler code here
    SetDlgItemText(IDC_EDIT_HELP,
        "�ؿ��ع��ܣ�m��     �޲���\r\n"
        "�迴��Ѳ��ɨ�裨m�� -data2 m	m:sequenceNO(0-7)\r\n"
        "�迴�ػ���ɨ�裨m�� -data2 m	m:patternNO(0-7)\r\n"
        "�迴������ɨ��      -data2 m	m:autopanNO(0-7)\r\n"
        "�迴��Ԥ��λ        -data2 m 	m:presetNO(0-7)\r\n"
        "�����ʱ��          -data2 m 	m:time(2-255)\r\n"
        );

    m_cmbCMD.ResetContent();
    m_cmbCMD.AddString("�ؿ��ع���");
    m_cmbCMD.AddString("�迴��Ѳ��ɨ��");
    m_cmbCMD.AddString("�迴�ػ���ɨ��");
    m_cmbCMD.AddString("�迴������ɨ��");
    m_cmbCMD.AddString("�迴��Ԥ��λ");
    m_cmbCMD.AddString("�����ʱ��");
}

void CPTZ20Dlg::OnRadioRegion() 
{
    SetDlgItemText(IDC_EDIT_HELP,
        "������ָʾ����λ��m�� -data2 m	m:RegionNO(0-7)\r\n"
        "������ָʾ����λ��m�� -data2 m	m:RegionNO(0-7)\r\n"
        "ɾ������ָʾ          -data2 m	m:RegionNO(0-7)\r\n"
        "���������⣨m��     �޲���\r\n"
        );

    m_cmbCMD.ResetContent();
    m_cmbCMD.AddString("������ָʾ����λ");
    m_cmbCMD.AddString("������ָʾ����λ");
    m_cmbCMD.AddString("ɾ������ָʾ");
    m_cmbCMD.AddString("����������");
}

void CPTZ20Dlg::OnRadioTitle() 
{
    SetDlgItemText(IDC_EDIT_HELP,
        "ȫ�������־���� -data2 x	x: 0/1=��/��\r\n"
        "ȫ�����⿪��     -data2 x	x: 0/1=��/��\r\n"
        "������⿪��     -data2 x	x: 0/1=��/��\r\n"
        "Ԥ��λ���⿪��   -data2 x	x:(0-7) 0/1=��/��      2~7 ��ͬģʽ\r\n"
        "�Զ�ɨ����⿪�� -data2 x	x:(0-7) 0/1=��/��      2~7 ��ͬģʽ\r\n"
        "Ѳ��ɨ����⿪�� -data2 x	x:(0-7) 0/1=��/��      2~7 ��ͬģʽ\r\n"
        "����ɨ����⿪�� -data2 x	x:(0-7) 0/1=��/��      2~7 ��ͬģʽ\r\n"
        "����ָʾ��־���� -data2 x	x:(0-7) 0/1=��/��      2~7 ��ͬģʽ\r\n"
        "����ָʾ��־���� -data2 x	x:(0-7) 0/1=��/��      2~7 ��ͬģʽ\r\n"
        "����ָʾ��־���� -data2 x	x:(0-7) 0/1=��/��      2~7 ��ͬģʽ\r\n"
        "�¶�ָʾ��־���� -data2 x	x: 0/1=��/��\r\n"
        "��ѹָʾ��־���� -data2 x	x: 0/1=��/��\r\n"
        "ϵͳʱ����ʾ���� -data2 x	x: 0/1=��/��\r\n"
        "ϵͳ������ʾ���� -data2 x	x: 0/1=��/��\r\n"
        "�ն�ָʾ��־���� -data2 x	x: 0/1=��/��\r\n"
        "����ָʾ��־���� -data2 x	x: 0/1=��/��\r\n"
        );

    m_cmbCMD.ResetContent();
    m_cmbCMD.AddString("ȫ�������־����");
    m_cmbCMD.AddString("ȫ�����⿪��");
    m_cmbCMD.AddString("������⿪��");
    m_cmbCMD.AddString("Ԥ��λ���⿪��");
    m_cmbCMD.AddString("�Զ�ɨ����⿪��");
    m_cmbCMD.AddString("Ѳ��ɨ����⿪��");
    m_cmbCMD.AddString("����ɨ����⿪��");
    m_cmbCMD.AddString("����ָʾ��־����");
    m_cmbCMD.AddString("����ָʾ��־����");
    m_cmbCMD.AddString("����ָʾ��־����");
    m_cmbCMD.AddString("�¶�ָʾ��־����");
    m_cmbCMD.AddString("��ѹָʾ��־����");
    m_cmbCMD.AddString("ϵͳʱ����ʾ����");
    m_cmbCMD.AddString("ϵͳ������ʾ����");
    m_cmbCMD.AddString("�ն�ָʾ��־����");
    m_cmbCMD.AddString("����ָʾ��־����");
}

void CPTZ20Dlg::OnRadioSys() 
{
    SetDlgItemText(IDC_EDIT_HELP,
        "���ݴ���         -data1 x x:��0~8���� \r\n"
        "                     0��ϵͳ������ \r\n"
        "                     1��ϵͳĬ��ֵ \r\n"
        "                     2��ɾ��Ԥ��λ���� \r\n"
        "                     3��ɾ������ɨ������ \r\n"
        "                     4��ɾ��Ѳ��ɨ������ \r\n"
        "                     5��ɾ��ģʽɨ������ \r\n"
        "                     6��ɾ������������� \r\n"
        "                     7��ɾ����˽�������� \r\n"
        "                     8��ɾ��������� \r\n"
        "���λ�ù���     -data1 x x:��0~2����0:���������� 1:ˮƽ��ת  2����̨ԭ��\r\n"
        "��Ļ��Ϣ����     -data2 x X:(0~1)  0:����ģʽ  1������ģʽ\r\n"
        "������������ģʽ -data2 x X:(0~3)  0:��������Զ�ģʽ  1:������ƽ���ģʽ   2:��������е�ģʽ    3:�������Զ��ģʽ\r\n"
        "�������ģʽ     -data2 x x:(0-3)ģʽ  0:��  1���۽�����2����Ȧ    3����\r\n"
        "ң���Զ��ָ�ģʽ -data2 x x:(0-255)\r\n"
        "�Զ��۽��ָ�ʱ�� -data2 x x:(0-255)\r\n"
        "�Զ���Ȧ�ָ�ʱ�� -data2 x x:(0-255)\r\n"
        "OSD�ַ���ɫ      -data2 x x:(0-8)\r\n"
        "OSDˮƽλ��      -data2 x x:(0-7)\r\n"
        "OSD��ֱλ��      -data2 x x:(0-63)\r\n"
        "�նȼ��ģʽ     -data2 x x:(0-1)\r\n"
        "�����նȷ�ֵ     -data2 x x:(0-10)\r\n"
        "��̨�˵�         -data2 x x:(0-1)\r\n"
        "������˵�       -data2 x x:(0-1)\r\n"
        "��ֱ�˶���Χ     -data2 x x:(0-10)\r\n"
        "ˮƽ�ֶ��ٶȵȼ� -data2 x x:(0-9)\r\n"
        "��ֱ�˶���Χ     -data2 x x:(0-9)\r\n"
        "�¶ȵ�λ         -data2 x x:(0-1)\r\n"
        "�佹ת������     -data2 x x:0��  1 ��\r\n"
        "��ˢ����         -data2 x x:0��  1 ��\r\n"
        "���ȿ���         -data2 x x:(0-7) ��/��    30/35/40/45/50/55\r\n"
        "���ȿ���         -data2 x x:(0-7) ��/��    5/0/-5/-10/-15/-20\r\n"
        "��Ļ��Ϣ����     -data2 x x:(0-12)\r\n"
        "��ת��ɫʱ��     -data1 h -data2 m H:Сʱ��0~23��  M;����(0~59)\r\n"
        "��ת�ڰ�ʱ��     -data1 h -data2 m H:Сʱ��0~23��  M;����(0~59)\r\n"
        "��̨�Զ�������   �޲���\r\n"
        "��̨�Զ�������   -data1 h -data2 m H:Сʱ��0~23��  M;����(0~59)\r\n"
        "��ʼ����Ϣ����   -data2 T T:ʱ�䣨0~255��   0����ʼ����Ϣ\r\n"
        );

    m_cmbCMD.ResetContent();
    m_cmbCMD.AddString("���ݴ���");
    m_cmbCMD.AddString("���λ�ù���");
    m_cmbCMD.AddString("��Ļ��Ϣ����");
    m_cmbCMD.AddString("������������ģʽ");
    m_cmbCMD.AddString("�������ģʽ");
    m_cmbCMD.AddString("ң���Զ��ָ�ģʽ");
    m_cmbCMD.AddString("�Զ��۽��ָ�ʱ��");
    m_cmbCMD.AddString("�Զ���Ȧ�ָ�ʱ��");
    m_cmbCMD.AddString("OSD�ַ���ɫ");
    m_cmbCMD.AddString("OSDˮƽλ��");
    m_cmbCMD.AddString("OSD��ֱλ��");
    m_cmbCMD.AddString("�նȼ��ģʽ");
    m_cmbCMD.AddString("�����նȷ�ֵ");
    m_cmbCMD.AddString("��̨�˵�");
    m_cmbCMD.AddString("������˵�");
    m_cmbCMD.AddString("��ֱ�˶���Χ");
    m_cmbCMD.AddString("ˮƽ�ֶ��ٶȵȼ�");
    m_cmbCMD.AddString("��ֱ�˶���Χ");
    m_cmbCMD.AddString("�¶ȵ�λ");
    m_cmbCMD.AddString("�佹ת������");
    m_cmbCMD.AddString("��ˢ����");
    m_cmbCMD.AddString("���ȿ���");
    m_cmbCMD.AddString("���ȿ���");
    m_cmbCMD.AddString("��Ļ��Ϣ����");
    m_cmbCMD.AddString("��ת��ɫʱ��");
    m_cmbCMD.AddString("��ת�ڰ�ʱ��");
    m_cmbCMD.AddString("��̨�Զ�������");
    m_cmbCMD.AddString("��̨�Զ�������");
    m_cmbCMD.AddString("��ʼ����Ϣ����");
}

void CPTZ20Dlg::OnRadioDarm() 
{
    // TODO: Add your control notification handler code here
    SetDlgItemText(IDC_EDIT_HELP,
        "��ѯ��������״̬��m���޲���\r\n"
        "���ر�������״��m��  -data2 m	m: 0���Ͽ�1���պ�\r\n"
        "�����������         -data2 m	m: 0���Ͽ�1���պ�\r\n"
        "�����ϴ�ģʽ��m��    -data2 m	m: 0:���������ϴ�ģʽ\r\n"
        "                                  1:�Զ������ϴ�ģʽ��ÿ��һ��\r\n"
        "                                  2:�Զ��仯�ϴ�ģʽ����������״̬���ͱ仯ʱ���ϴ�����\r\n"
        );

    m_cmbCMD.ResetContent();
    m_cmbCMD.AddString("��ѯ��������״̬");
    m_cmbCMD.AddString("���ر�������״");
    m_cmbCMD.AddString("�����������");
    m_cmbCMD.AddString("�����ϴ�ģʽ");
}

void CPTZ20Dlg::OnRadioInq() 
{
    SetDlgItemText(IDC_EDIT_HELP,
        "�����豸����                �޲���\r\n"
        "�����豸����״̬            �޲���\r\n"
        "����ˮƽλ��                �޲���\r\n"
        "������̨λ��                �޲���\r\n"
        "�������λ��                �޲���\r\n"
        "�����豸ϵ�к�              �޲���\r\n"
        "�����豸�ͺ�                �޲���\r\n"
        "����������ͺ�              �޲���\r\n"
        "�����������汾��          �޲���\r\n"
        "����ʱ��                    �޲���\r\n"

        "��������¶�               -data2 x X:0~3\r\n"
        "�����豸��ѹ               -data2 x X:0~3\r\n"
        "��������ٶ�               -data2 x X:0~3\r\n"
        "���������ѹ               -data2 x X:0~3\r\n"
        "�����������               -data2 x X:0~3\r\n"
        "����Ԥ��λ����             -data2 x X:1~255\r\n"
        "��������ɨ�����           -data2 x X:0~7\r\n"
        "����Ѳ��ɨ�����           -data2 x X:0~7\r\n"
        "������ɨ�����           -data2 x X:0~7\r\n"
        "��������ָʾ����           -data2 x X:0~7\r\n"
        "�������������汾         �޲���\r\n"
        );

    m_cmbCMD.ResetContent();
    m_cmbCMD.AddString("�����豸����");
    m_cmbCMD.AddString("�����豸����״̬");
    m_cmbCMD.AddString("����ˮƽλ��");
    m_cmbCMD.AddString("������̨λ��");
    m_cmbCMD.AddString("�������λ��");
    m_cmbCMD.AddString("�����豸ϵ�к�");
    m_cmbCMD.AddString("�����豸�ͺ�");
    m_cmbCMD.AddString("����������ͺ�");
    m_cmbCMD.AddString("�����������汾��");
    m_cmbCMD.AddString("����ʱ��");

    m_cmbCMD.AddString("��������¶�");
    m_cmbCMD.AddString("�����豸��ѹ");
    m_cmbCMD.AddString("��������ٶ�");
    m_cmbCMD.AddString("���������ѹ");
    m_cmbCMD.AddString("�����������");
    m_cmbCMD.AddString("����Ԥ��λ����");
    m_cmbCMD.AddString("��������ɨ�����");
    m_cmbCMD.AddString("����Ѳ��ɨ�����");
    m_cmbCMD.AddString("������ɨ�����");
    m_cmbCMD.AddString("��������ָʾ����");
    m_cmbCMD.AddString("�������������汾");
}

void CPTZ20Dlg::OnRadioVar() 
{
    SetDlgItemText(IDC_EDIT_HELP,
        "����ˮƽλ��       -packet d-d-d\r\n"
        "������̨λ��       -packet d-d-d-d-d\r\n"
        "�������λ��       -packet d-d-d-d-d-d-d\r\n"
        "�����豸ϵ�к�     -packet string  \r\n"
        "����ʱ��           -packet Y-M-D-W-h-m-s\r\n"
        "�����������       -packet string\r\n"
        "����Ԥ��λ����     -packet ID-string  Ԥ��λID(1-255)-string\r\n"
        "��������ɨ�����   -packet ID-string  ɨ��ID(0~7)-string \r\n"
        "����Ѳ��ɨ�����   -packet ID-string  ɨ��ID(0~7)-string \r\n"
        "���û���ɨ�����   -packet ID-string  ɨ��ID(0~7)-string \r\n"
        "��������ָʾ����   -packet ID-string  ����ָʾ��(0~7)--string \r\n"
        "������˽����       -packet ID-W-H ����ţ�0-23��W :�����1-80�� H ������ߣ�1-60��\r\n"
        "��ά���ܶ�λ1      -packet Xs-Ys-Xe-Ye Xs(0-255)�������x Ys(0-255)�������y    Xe(0-255���յ�����x    Ye(0-255)�յ�����y\r\n"
        "��ά���ܶ�λ2      -packet Xs-Ys-Xe-Ye Xs(0-255)�������x Ys(0-255)�������y    Xe(0-255���յ�����x    Ye(0-255)�յ�����y \r\n"
        "��ά���ܶ�λ3      -packet Xs-Ys-Xe-Ye Xs(0-255)�������x Ys(0-255)�������y    Xe(0-255���յ�����x    Ye(0-255)�յ�����y \r\n"
        "��������           -packet B1-B2-B3-B4-B5-B6-B7-B8-B9-B10-B11-B12\r\n"
        "                           B1:  ����ͨ����0-7 \r\n"
        "                           B2:  ����ģʽ  0 �ֶ�������1�Զ�������\r\n"
        "                           B3�� ����״̬  1������ 0�� ���� \r\n"
        "                           B4�� ����״̬  0  ������Ч  1 ������Ч \r\n"
        "                           B5�� �������  0: Ѳ��ɨ�� 1 ģʽɨ��  2 ����ɨ��  3Ԥ��λ \r\n"
        "                           B6�� ����ID Ѳ����0-7�� \r\n"
        "                                ģʽɨ�裨0-7���� ����ɨ�裨0-7���� Ԥ��λ��1-255�� \r\n"
        "                           B7�� �����ʽ��0�Ͽ���1�պ� \r\n"
        "                           B8�� �ӳ�ʱ�� 1��255 Ĭ��20 \r\n"
        "                           B9�� ����ʱ�� H ʱ \r\n"
        "                           B10������ʱ�� M �� \r\n"
        "                           B11������ʱ�� H ʱ \r\n"
        "                           B12: ����ʱ�� M �� \r\n"
        "��ʾ��Ļ��Ϣ       -packet B1-B2-B3-B4-string "
        "                           B1��������0-39  \r\n"
        "                           B2��������0-12  \r\n"
        "                           B3���ַ�����ʾ����0-3 ȫ͸�� ȫ͸+��˸�� ��͸�� ��͸+��˸\r\n"
        "                           B4���ַ���ɫ  0-7  ��ɫ����ɫ����ɫ�� ��ɫ����ɫ����ɫ�� ��ɫ�� ��ɫ��\r\n"
        "�����豸Ʒ��       -packet string String:��Ҫ���õ�Ʒ���ַ���\r\n"
        );

    m_cmbCMD.ResetContent();
    m_cmbCMD.AddString("����ˮƽλ��");
    m_cmbCMD.AddString("������̨λ��");
    m_cmbCMD.AddString("�������λ��");
    m_cmbCMD.AddString("�����豸ϵ�к�");
    m_cmbCMD.AddString("����ʱ��");
    m_cmbCMD.AddString("�����������");
    m_cmbCMD.AddString("����Ԥ��λ����");
    m_cmbCMD.AddString("��������ɨ�����");
    m_cmbCMD.AddString("����Ѳ��ɨ�����");
    m_cmbCMD.AddString("���û���ɨ�����");

    m_cmbCMD.AddString("��������ָʾ����");
    m_cmbCMD.AddString("������˽����");
    m_cmbCMD.AddString("��ά���ܶ�λ1");
    m_cmbCMD.AddString("��ά���ܶ�λ2");
    m_cmbCMD.AddString("��ά���ܶ�λ3");
    m_cmbCMD.AddString("��������");
    m_cmbCMD.AddString("��ʾ��Ļ��Ϣ");
    m_cmbCMD.AddString("�����豸Ʒ��");
}

void CPTZ20Dlg::OnRadioCmr() 
{
    // TODO: Add your control notification handler code here
    SetDlgItemText(IDC_EDIT_HELP,
        "�ָ������Ĭ��ֵ  -data2  x x(0~1)		0:���������Ҫ�󣬻ָ������ȫ������Ĭ��ֵ 1���ָ����ȣ��Աȶȣ�ɫ���Ͷȣ���ȣ�AGC��ֵ�Ȳ���Ĭ��ֵ\r\n"
        "������ϵ縴λ    -data2  x x:(0~1)	0:������ϵ縴λ 1:����������λ\r\n"
        "AEģʽ            -data1 x -data2 v x:(0~4)ģʽ	0:AE�Զ�ģʽ 1:AE��������ģʽ	2:AE��Ȧ����ģʽ 3:AE��������ģʽ	4:AE��������ģʽ   v:(0~31)ģʽֵ\r\n"
        "BLC���           -data1 x -data2 v x:(0~2)ģʽ	0:BLC�ر�	1:BLCģʽ	2:WDRģʽ  v:(0~255)��Χֵ\r\n"
        "��ƽ��ģʽ        -data1 x  -data2 v \r\n"
        "                      ע�⣺xΪ��ֵͬʱ��v�в�ͬ���� \r\n"
        "                            x=0 ��ƽ��ģʽ,v����0~5���Զ����ֶ������١����ڡ����⡢���� \r\n"
        "                            x=1 R����         v:(0~255) \r\n"
        "                            x=2 B ����        v:(0~255) \r\n"
        "                            x=3 �Զ���ȦALC   v:(0~255) \r\n"
        "                            x=4 �Զ���ȦPLC   v:(0~255) \r\n"
        "                            x=5 ���ֱ佹      v:(0-12) ��0Ϊ�� \r\n"
        "                            x=6 ����������    v:(0-12) ��0Ϊ�� \r\n"
        "                            x=7 AGC��ֵ       v:(0~255) \r\n"
        "                            x=8  ͼ������     v:(0~255) \r\n"
        "                            x=9  ͼ��Աȶ�   v:(0~255) \r\n"
        "                            x=10 ͼ��ɫ���Ͷ� v:(0~255) \r\n"
        "                            x=11 ͼ�����     v:(0~255) \r\n"
        "                            x=12 �佹�ٶ�     v:(0~255) \r\n"
        "                            x=13 �۽��ٶ�     v:(0~7) \r\n"
        "                            x=14 ��С�۽����� v:(0~7) \r\n"
        "                            x=15 ͼ����DNR  v:(0-15) \r\n"
        "                            x=16 �ڲ�ת��     v:(0-3)A/D/N/T \r\n"
        "                            x=17 ͼ�񶳽�     v:0 �أ�1 �� \r\n"
        "                            x=18 ͼ��ˮƽ���� v:0 �أ�1 �� \r\n"
        "                            x=19 ͼ��ֱ���� v:0 �أ�1 �� \r\n"
        "                            x=20 ͼ��Ƭ     v:0 �أ�1 �� \r\n"
        "                            x=21 ͼ���ȶ�     v:0 �أ�1 �� \r\n"

        "ͼ��ˮƽλ��  -data1 x x:(0-1920)\r\n"
        "ͼ��ֱλ��  -data1 x x:(0-1080)\r\n"
        "��˽������  -data1 x -data2 m x:(0-23) ����ID m:(0~2)  0:��ʾ��˽����  1:������˽����  2:ɾ����˽����\r\n"
        "������˽������ɫ  -data1 x -data2 c x:(0-23) C:(0-8)��ɫ\r\n"
        );

    m_cmbCMD.ResetContent();
    m_cmbCMD.AddString("�ָ������Ĭ��ֵ");
    m_cmbCMD.AddString("������ϵ縴λ");
    m_cmbCMD.AddString("AEģʽ");
    m_cmbCMD.AddString("BLC���");
    m_cmbCMD.AddString("��ƽ��ģʽ");
    m_cmbCMD.AddString("ͼ��ˮƽλ��");
    m_cmbCMD.AddString("ͼ��ֱλ��");
    m_cmbCMD.AddString("��˽������");
    m_cmbCMD.AddString("������˽������ɫ");
}

void CPTZ20Dlg::OnRadioProduce() 
{
    // TODO: Add your control notification handler code here
    SetDlgItemText(IDC_EDIT_HELP,
        "��Ҫָ��*        �޲��� \r\n"
        "����ڴ�*        �޲��� \r\n"
        "��������*        �޲��� \r\n"
        "Ĭ������*        �޲��� \r\n"
        "Ӳ������*        �޲��� \r\n"
        "�ϻ�����*        �޲��� \r\n"
        "��ʼ������*      �޲���   \r\n"
        "����������ͺ�*  -data2 x  �ֶι���  \r\n"
        "���������ַ*    -data2 x  x:(1-255) \r\n"
        "��ˢλ�õ���*    -data2 x  x:(0-20) \r\n"
        "��ֱλ�õ���*    -data2 x  x:(0-20) \r\n"
        "���ò˵�����*    -data1 e -data2 d e:(b7-b0)��������,��λ����1Ϊ��Ч  d��(b7-b0)��ǰ���ԣ�,��λ����1Ϊ��Ч��ֻ��ѡһ������  \r\n"
        "ֹͣӲ������     �޲���    \r\n"
        "ֹͣ�ϻ�����     �޲���    \r\n"
        "��ȡ�ϻ����Ա��� �޲���        \r\n"
        );

    m_cmbCMD.ResetContent();
    m_cmbCMD.AddString("��Ҫָ��*");
    m_cmbCMD.AddString("����ڴ�*");
    m_cmbCMD.AddString("��������*");
    m_cmbCMD.AddString("Ĭ������*");
    m_cmbCMD.AddString("Ӳ������*");
    m_cmbCMD.AddString("�ϻ�����*");
    m_cmbCMD.AddString("��ʼ������*");
    m_cmbCMD.AddString("����������ͺ�*");
    m_cmbCMD.AddString("���������ַ*");
    m_cmbCMD.AddString("��ˢλ�õ���*");
    m_cmbCMD.AddString("��ֱλ�õ���*");
    m_cmbCMD.AddString("���ò˵�����*");
    m_cmbCMD.AddString("ֹͣӲ������");
    m_cmbCMD.AddString("ֹͣ�ϻ�����");
    m_cmbCMD.AddString("��ȡ�ϻ����Ա���");
}
