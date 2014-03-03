using UnityEngine;
using System.Collections;

public class PrefabManager : MonoBehaviour {
	public GameObject prefPlayer;

	// Use this for initialization
	void Awake ()
	{
	}

	// Update is called once per frame
	void Update ()
	{
	
	}

	void InstantiatePlayer ()
	{
		Instantiate (prefPlayer, Vector3.zero, Quaternion.identity);
	}
}
