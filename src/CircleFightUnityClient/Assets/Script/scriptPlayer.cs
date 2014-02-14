using UnityEngine;
using System;
using System.Collections;
using System.Runtime.InteropServices;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;

public class PlayerInfo
{
	private float mX;
	private float mY;
	private float mVelocityX;
	private float mVelocityY;
	private float mAcceleration;
	private float mAngle;

	public PlayerInfo()
	{
		mX = mY = mVelocityX = mVelocityY = mAcceleration = mAngle = 0;
	}
	public PlayerInfo(float pX, float pY, float pVelocityX, float pVelocityY, float pAcceleration, float pAngle)
	{
		Init (pX, pY, pVelocityX, pVelocityY, pAcceleration, pAngle);
	}

	public void Init(float pX, float pY, float pVelocityX, float pVelocityY, float pAcceleration, float pAngle)
	{
		mX = pX;
		mY = pY;
		mVelocityX = pVelocityX;
		mVelocityY = pVelocityY;
		mAcceleration = pAcceleration;
		mAngle = pAngle;
	}

	public void Update()
	{
		mX = mX + mVelocityX * Time.deltaTime;
		mY = mY + mVelocityY * Time.deltaTime;

		mVelocityX = mVelocityX + mAcceleration * Time.deltaTime;
		mVelocityY = mVelocityY + mAcceleration * Time.deltaTime;
	}

	public void SetPosition (float pX, float pY)
	{
		mX = pX;
		mY = pY;
	}
	public void SetVelocity(float pVelocityX, float pVelocityY)
	{
		mVelocityX = pVelocityX;
		mVelocityY = pVelocityY;
	}
	public void SetVelocityX(float pVelocityX)
	{
		mVelocityX = pVelocityX;
	}
	public void SetVelocityY(float pVelocityY)
	{
		mVelocityY = pVelocityY;
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
