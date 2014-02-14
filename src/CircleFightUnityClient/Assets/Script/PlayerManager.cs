using UnityEngine;
using System.Collections;

public class PlayerManager : MonoBehaviour {
	public GameObject prefPlayer;
	
	public class Player
	{
		private GameObject mGameObject;
		private float mX;
		private float mY;
		private float mVelocityX;
		private float mVelocityY;
		private float mAcceleration;
		private float mAngle;
		
		public Player()
		{
			mX = mY = mVelocityX = mVelocityY = mAcceleration = mAngle = 0;
		}
		public Player(float pX, float pY, float pVelocityX, float pVelocityY, float pAcceleration, float pAngle)
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

	private Player
	private GameObject newPlayer;

	// Use this for initialization
	void Start () {

		newPlayer = GameObject.Instantiate (prefPlayer, Vector3.zero, Quaternion.identity) as GameObject;
	
	}
	
	// Update is called once per frame
	void Update () {
	
		newPlayer.transform.Translate(Vector3.right * Time.deltaTime);
	}
}
