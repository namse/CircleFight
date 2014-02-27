using UnityEngine;
using System.Collections;

public class Player_I : MonoBehaviour {
	private float x_;
	private float y_;
	private float velocity_x_;
	private float velocity_y_;
	private float acceleration_;
	private float angle_;

	// Use this for initialization
	void Start ()
	{
		//Init (0, 0, 0, 0, 0, 0);
	}
	
	// Update is called once per frame
	void Update ()
	{
		Movement ();
		transform.Translate (Vector3.right * velocity_x_ * Time.deltaTime);
		transform.Translate (Vector3.right * velocity_y_ * Time.deltaTime);
		
		velocity_x_ = velocity_x_ + acceleration_ * Time.deltaTime;
		velocity_y_ = velocity_y_ + acceleration_ * Time.deltaTime;
	}

	void Movement()
	{
		if(Input.GetKey(KeyCode.W))
		{
			transform.Translate(Vector2.up * 3 * Time.deltaTime);
			Camera.main.transform.Translate(Vector2.up * 3 * Time.deltaTime);



			/*
			Network client;
			client = this.gameObject.GetComponent<Network>();
			client.Init ();
			data a;
			a.mSize = 8;
			a.mType = 1
			client.writer.Write (a.mSize);
			client.writer.Write (a.mType);
			client.writer.Flush ();
			*/
		}
		else if(Input.GetKey(KeyCode.S))
		{
			transform.Translate(Vector2.up * -3 * Time.deltaTime);
			Camera.main.transform.Translate(Vector2.up * -3 * Time.deltaTime);
		}

		if(Input.GetKey(KeyCode.A))
		{
			transform.Translate(Vector2.right * -3 * Time.deltaTime);
			Camera.main.transform.Translate(Vector2.right * -3 * Time.deltaTime);
		}
		else if(Input.GetKey(KeyCode.D))
		{
			transform.Translate(Vector2.right * 3 * Time.deltaTime);
			Camera.main.transform.Translate(Vector2.right * 3 * Time.deltaTime);
		}
	}
	public void Init(float x, float y, float velocity_x, float velocity_y, float acceleration, float angle)
	{
		SetPosition (x, y);
		SetVelocity (velocity_x, velocity_y);
		SetAcceleration (acceleration);
		SetAngle (angle);
	}
	
	public void SetPosition (float x, float y)
	{
		x_ = x;
		y_ = y;
		transform.position = new Vector3(x_, y_);
	}
	public void SetVelocity(float velocity_x, float velocity_y)
	{
		velocity_x_ = velocity_x;
		velocity_y_ = velocity_y;
	}
	public void SetVelocity_x(float velocity_x)
	{
		velocity_x_ = velocity_x;
	}
	public void SetVelocity_y(float velocity_y)
	{
		velocity_y_ = velocity_y;
	}
	public void SetAcceleration(float acceleration)
	{
		acceleration_ = acceleration;
	}
	public void SetAngle(float angle)
	{
		angle_ = angle;
		transform.rotation = Quaternion.AngleAxis (angle_, Vector3.right);
	}
	
	public float GetAngle()
	{
		return angle_;
	}
}
