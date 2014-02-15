using UnityEngine;
using System.Collections;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

public class Player : MonoBehaviour {
	[System.Serializable]
	public struct Player_Info
	{
		public float x_;
		public float y_;
		public float velocity_x_;
		public float velocity_y_;
		public float acceleration_;
		public float angle_;
	}

	Player_Info pi_ = new Player_Info ();
	
	// Use this for initialization
	void Start ()
	{
		Init (0, 0, 0, 0, 0, 0);
	}
	
	// Update is called once per frame
	void Update ()
	{
		transform.Translate (Vector3.right * pi_.velocity_x_ * Time.deltaTime);
		transform.Translate (Vector3.right * pi_.velocity_y_ * Time.deltaTime);
		
		pi_.velocity_x_ = pi_.velocity_x_ + pi_.acceleration_ * Time.deltaTime;
		pi_.velocity_y_ = pi_.velocity_y_ + pi_.acceleration_ * Time.deltaTime;

		if (Input.GetMouseButtonDown (0))
		{
			SetPosition(0.5f, -0.5f);
			BinaryFormatter bf = new BinaryFormatter();
			MemoryStream ms = new MemoryStream();
			bf.Serialize(ms, pi_);
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
		pi_.x_ = x;
		pi_.y_ = y;
		transform.position = new Vector3(pi_.x_, pi_.y_);
	}
	public void SetVelocity(float velocity_x, float velocity_y)
	{
		pi_.velocity_x_ = velocity_x;
		pi_.velocity_y_ = velocity_y;
	}
	public void SetVelocity_x(float velocity_x)
	{
		pi_.velocity_x_ = velocity_x;
	}
	public void SetVelocity_y(float velocity_y)
	{
		pi_.velocity_y_ = velocity_y;
	}
	public void SetAcceleration(float acceleration)
	{
		pi_.acceleration_ = acceleration;
	}
	public void SetAngle(float angle)
	{
		pi_.angle_ = angle;
		transform.rotation = Quaternion.AngleAxis (pi_.angle_, Vector3.right);
	}
	
	public float GetAngle()
	{
		return pi_.angle_;
	}
}
