using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;
using System;
using System.IO;
using System.Net;
using System.Net.Sockets;

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
			Debug.Log ("소켓 연결");
		}
		catch (Exception e)
		{
			Debug.Log("Socket error : " + e);
		}
	}
}
