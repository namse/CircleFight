using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;
using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using packet_type;

public class Network : MonoBehaviour {
	// Packet Header
	struct PacketHeader{
		public short size;
		public short type;
	};
	// Packet From
	public const int	PKT_NONE = 0;
	public const int 	PKT_CS_LOGIN = 1;
	public const int	PKT_SC_LOGIN = 2;
	public const int	PKT_SC_LOGIN_BROADCAST = 3;
	// Packet To

	// Socket
	public bool socket_ready;
	public TcpClient socket;
	public NetworkStream stream;
	public BinaryWriter writer;
	public BinaryReader reader;

	// Use this for initialization
	void Awake ()
	{
		try
		{
			socket = new TcpClient ("127.0.0.1", 9001);
			stream = socket.GetStream ();
			writer = new BinaryWriter (stream);
			reader = new BinaryReader (stream);

			socket.NoDelay = true;
			socket.ReceiveTimeout = 1;
			
			Debug.Log ("Socket Success");
		}
		catch (Exception e)
		{
			Debug.Log("Socket error : " + e);
		}
	}
	
	// Update is called once per frame
	void Update ()
	{
		//if (Input.GetMouseButtonDown (0))
		//{
			//
		//}
	}

	public void SendPacket(short type, global::ProtoBuf.IExtensible packet)
	{
		byte[] byte_array;
		MemoryStream memory_stream = new MemoryStream ();
		ProtoBuf.Serializer.Serialize (memory_stream, packet);
		byte_array = memory_stream.ToArray ();

		writer.Write ((short)(byte_array.Length));
		writer.Write ((short)(type));
		writer.Write (byte_array);
		writer.Flush ();
	}

	public void ReadPacket()
	{
		if (!socket_ready)
		{
			return;
		}

		try
		{
			short size, type;
			byte[] bytes;
			size = reader.ReadInt16 ();
			type = reader.ReadInt16 ();
			bytes = reader.ReadBytes (size);

			if(bytes.Length != size)
			{
				// Packet Error : Lost Payload or Controlled
			}
			//////////////////////
			// Read Byte Arrays //
			//////////////////////
		} catch(Exception e)
		{
			// Error
			return;
		}
	}

	public void Init()
	{
		try
		{
			Debug.Log ("소켓 연결");
		}
		catch (Exception e)
		{
			Debug.Log("Socket error : " + e);
		}
	}
}
