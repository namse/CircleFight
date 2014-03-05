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
	struct PacketHeader
	{
		public short size;
		public short type;
	};
	// Packet From
	public const short	PKT_NONE = 0;
	public const short 	PKT_CS_LOGIN = 1;
	public const short	PKT_SC_LOGIN = 2;
	public const short	PKT_SC_LOGIN_BROADCAST = 3;
	public const short	PKT_CS_MOVE_KEY_CHNAGE = 4;
	public const short	PKT_MAX = 5;
	// Packet To

	// Socket
	public bool socket_ready = false;
	public TcpClient socket;
	public NetworkStream stream;
	public BinaryWriter writer;
	public BinaryReader reader;

	public bool did_w_pressed_ = false;
	public bool did_a_pressed_ = false;
	public bool did_s_pressed_ = false;
	public bool did_d_pressed_ = false;
	// Use this for initialization
	void Start ()
	{
		try
		{
			socket = new TcpClient ("127.0.0.1", 9001);
			stream = socket.GetStream ();
			writer = new BinaryWriter (stream);
			reader = new BinaryReader (stream);

			socket.NoDelay = true;
			socket.ReceiveTimeout = 1;

			socket_ready = true;
			Debug.Log ("Socket Connection Success");

			LoginRequest login_request = new LoginRequest();
			SendPacket(PKT_CS_LOGIN, login_request);
			
			StartCoroutine("ReadPacket");

		}
		catch (Exception e)
		{
			Debug.Log("Socket Connection Error : " + e);
		}
	}
	
	// Update is called once per frame
	void Update ()
	{
		//if (Input.GetMouseButtonDown (0))
		//{
			//
		//}
		if ( (Input.GetKey (KeyCode.W)^ did_w_pressed_ == true)
		    || (Input.GetKey (KeyCode.A)^ did_a_pressed_ == true)
		    || (Input.GetKey (KeyCode.S)^ did_s_pressed_ == true)
		    || (Input.GetKey (KeyCode.D)^ did_d_pressed_ == true)){
			did_w_pressed_ = Input.GetKey(KeyCode.W);
			did_a_pressed_ = Input.GetKey(KeyCode.A);
			did_s_pressed_ = Input.GetKey(KeyCode.S);
			did_d_pressed_ = Input.GetKey(KeyCode.D);

			MoveKeyPressRequest move_request = new MoveKeyPressRequest();
			move_request.move_key_w_press = did_w_pressed_;
			move_request.move_key_a_press = did_a_pressed_;
			move_request.move_key_s_press = did_s_pressed_;
			move_request.move_key_d_press = did_d_pressed_;
			SendPacket(PKT_CS_MOVE_KEY_CHNAGE, move_request);
		}
	}

	public void SendPacket(short type, global::ProtoBuf.IExtensible packet)
	{
		if (!socket_ready)
		{
			return;
		}

		MemoryStream memory_stream = new MemoryStream ();
		ProtoBuf.Serializer.Serialize (memory_stream, packet);
		byte[] byte_array = memory_stream.ToArray ();

		writer.Write ((short)(byte_array.Length));
		writer.Write ((short)(type));
		writer.Write (byte_array);
		writer.Flush ();
	}

	IEnumerator ReadPacket()
	{
		while (socket_ready)
		{
			yield return 0;
			
			try
			{
				short size = 0;
				short type = 0;
				byte[] bytes;
				size = reader.ReadInt16 ();
				type = reader.ReadInt16 ();
				bytes = reader.ReadBytes (size);
				
				if(bytes.Length != size)
				{
					// Packet Error : Lost Payload or Controlled
				}
				
				if(0 <= type && type < PKT_MAX)
				{
					MemoryStream memory_stream = new MemoryStream();
					memory_stream.Write(bytes, 0, size);
					BinaryReader binary_reader = new BinaryReader(memory_stream);
					
					switch(type)
					{
					case PKT_NONE:
					{
						break;
					}
					case PKT_SC_LOGIN:
					{
						Debug.Log ("Size : " + size + ", type : " + type + ", player_id : " + binary_reader.ReadInt32());
						break;
					}
					}
					// Check Packet
				}
				
				// Push to MemoryStream
			} catch(Exception e)
			{
				Debug.Log ("Read to Socket Error : " + e);
			}
		}
	}
}
