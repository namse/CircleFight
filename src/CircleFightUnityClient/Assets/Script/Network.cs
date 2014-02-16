using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;
using System;
using System.IO;
using System.Net;
using System.Net.Sockets;

using PacketType;

public class Network : MonoBehaviour {
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

			PacketHeader ph = new PacketHeader();
			ph.size = 8;
			ph.type = PacketType.PacketType.PKT_CS_LOGIN;

			LoginRequest a = new LoginRequest();
			a.header = ph;

			byte[] bt;
			MemoryStream ms = new MemoryStream();
			ProtoBuf.Serializer.Serialize(ms, a);
			bt = ms.ToArray ();

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
