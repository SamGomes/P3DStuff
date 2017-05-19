using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class RotatePlayerArrow : MonoBehaviour {

    public GameObject fromObject = null;
    public Image toImage = null;

	// Use this for initialization
	void Update () {
        toImage.rectTransform.rotation = Quaternion.Euler(0,0,-fromObject.transform.eulerAngles.y);	
	}
}
