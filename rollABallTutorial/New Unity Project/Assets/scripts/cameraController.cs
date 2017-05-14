using UnityEngine;
using System.Collections;

public class cameraController : MonoBehaviour {
    public GameObject player;
    private Vector3 offset;

	// Use this for initialization
	void Start () {
        offset = transform.position -  player.transform.position;
    }
	
	// Update is called once per frame
	void LateUpdate () {


        offset = Quaternion.AngleAxis(Input.GetAxis("Mouse X") * 2, Vector3.up) * offset;
        transform.position = player.transform.position + offset;
        transform.LookAt(player.transform);
    }
}
