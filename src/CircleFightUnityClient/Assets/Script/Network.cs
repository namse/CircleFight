using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;
using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using packet_type;

public class Network : MonoBehaviour {
	struct PacketHeader{
		public short size;
		public short type;
	};
	public const int	PKT_NONE = 0;
	public const int 	PKT_CS_LOGIN = 1;
	public const int	PKT_SC_LOGIN = 2;
	public const int	PKT_SC_LOGIN_BROADCAST = 3;

	public TcpClient socket;
	public NetworkStream stream;
	public BinaryWriter writer;
	public BinaryReader reader;
	
	public GameObject prefPlayer;

	// Use this for initialization
	void Start ()
	{
	}
	
	// Update is called once per frame
	void Update ()
	{
		if (Input.GetMouseButtonDown (0))
		{
			//Instantiate (prefPlayer, Vector3.zero, Quaternion.identity);
		}
	}

	public void Init()
	{
		try
		{
			socket = new TcpClient ("127.0.0.1", 9001);
			stream = socket.GetStream ();
			writer = new BinaryWriter (stream);
			reader = new BinaryReader (stream);

			PacketHeader packet_header;
			packet_header.type = PKT_CS_LOGIN;
			LoginRequest login_request = new LoginRequest();

			byte[] bt;
			MemoryStream ms = new MemoryStream();
			ProtoBuf.Serializer.Serialize(ms, login_request);
			bt = ms.ToArray ();
			packet_header.size = (short)bt.Length;

			writer.Write(packet_header.size);
			writer.Write(packet_header.type);
			writer.Write(bt);
			writer.Flush ();

			Debug.Log ("소켓 연결");
		}
		catch (Exception e)
		{
			Debug.Log("Socket error : " + e);
		}
	}
}
