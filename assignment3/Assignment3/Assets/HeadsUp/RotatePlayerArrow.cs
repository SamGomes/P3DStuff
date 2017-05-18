using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class RotatePlayerArrow : MonoBehaviour {

    public Camera fromCamera = null;
    public Image toImage = null;

	// Use this for initialization
	void Update () {
        Debug.Log("lalal");
        if(fromCamera != null && toImage != null)
            toImage.rectTransform.rotation.Set(0,0, fromCamera.transform.rotation.y,1);	
	}
}
