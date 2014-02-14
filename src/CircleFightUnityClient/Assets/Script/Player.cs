using UnityEngine;
using System.Collections;

public class Player : MonoBehaviour {
	private float x_;
	private float y_;
	private float velocity_x_;
	private float velocity_y_;
	private float acceleration_;
	private float angle_;
	
	// Use this for initialization
	void Start ()
	{
		Init (0, 0, 0, 0, 0, 0);
	}
	
	// Update is called once per frame
	void Update ()
	{
		transform.Translate (Vector3.right * velocity_x_ * Time.deltaTime);
		transform.Translate (Vector3.right * velocity_y_ * Time.deltaTime);
		
		velocity_x_ = velocity_x_ + acceleration_ * Time.deltaTime;
		velocity_y_ = velocity_y_ + acceleration_ * Time.deltaTime;
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
