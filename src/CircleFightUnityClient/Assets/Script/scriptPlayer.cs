using UnityEngine;
using System;
using System.Collections;
using System.Runtime.InteropServices;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;

public struct data{
	public int mSize;
	public short mType;
};

public class scriptPlayer : MonoBehaviour {
	

	Network client;
	float speed;

	SpriteRenderer spriteRenderer;
	Sprite thePerfab;
	Sprite instance;

	// Use this for initialization
	void Start ()
	{
		client = this.gameObject.GetComponent<Network>();
		client.Init ();
		speed = 1.0f;


	}
	
	// Update is called once per frame
	void Update ()
	{
		Movement ();
	}

	void Movement()
	{
		if(Input.GetKey(KeyCode.W))
		{
			transform.Translate(Vector2.up * speed * Time.deltaTime);
			Camera.main.transform.Translate(Vector2.up * speed * Time.deltaTime);


			data a;
			a.mSize = 10005;
			a.mType = 125;
/*			Buffer.BlockCopy(

			BinaryFormatter formatter = new BinaryFormatter();
			formatter.Serialize(client.stream,a);*/



			/*
			client.writer.Write (a.mSize);
			client.writer.Write (a.mType);
			client.writer.Flush ();
			*/
		}
		else if(Input.GetKey(KeyCode.S))
		{
			transform.Translate(Vector2.up * -speed * Time.deltaTime);
			Camera.main.transform.Translate(Vector2.up * -speed * Time.deltaTime);
		}

		if(Input.GetKey(KeyCode.A))
		{
			transform.Translate(Vector2.right * -speed * Time.deltaTime);
			Camera.main.transform.Translate(Vector2.right * -speed * Time.deltaTime);
		}
		else if(Input.GetKey(KeyCode.D))
		{
			transform.Translate(Vector2.right * speed * Time.deltaTime);
			Camera.main.transform.Translate(Vector2.right * speed * Time.deltaTime);
		}
	}
}
