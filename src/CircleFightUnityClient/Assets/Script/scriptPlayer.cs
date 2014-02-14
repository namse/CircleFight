using UnityEngine;
using System;
using System.Collections;
using System.Runtime.InteropServices;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Object;

public class PlayerInfo
{
	private float mX;
	private float mY;
	private float mVelocity;
	private float mAcceleration;
	private float mAngle;

	public PlayerInfo()
	{
		mX = mY = mVelocity = mAcceleration = mAngle = 0;
	}
	public PlayerInfo(float pX, float pY, float pVelocity, float pAcceleration, float pAngle)
	{
		Init (pX, pY, pVelocity, pAcceleration, pAngle);
	}

	public void Init(float pX, float pY, float pVelocity, float pAcceleration, float pAngle)
	{
		mX = pX;
		mY = pY;
		mVelocity = pVelocity;
		mAcceleration = pAcceleration;
		mAngle = pAngle;
	}

	public void SetPosition (float pX, float pY)
	{
		mX = pX;
		mY = pY;
	}
	public void SetVelocity(float pVelocity)
	{
		mVelocity = pVelocity;
	}
	public void SetAcceleration(float pAcceleration)
	{
		mAcceleration = pAcceleration;
	}
	public void SetAngle(float pAngle)
	{
		mAngle = pAngle;
	}

	public float GetAngle()
	{
		return mAngle;
	}
}
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

		spriteRenderer = gameObject.GetComponent<SpriteRenderer> ();
		thePerfab = spriteRenderer.sprite;
		instance = (Sprite)Instantiate (thePerfab, transform.position, transform.rotation);
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
