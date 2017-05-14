using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class PlayerController : MonoBehaviour
{
   
    private Rigidbody rb;
    public Text scoreText;

    public GameObject cameraObj;

    public float score;

    void Start()
    {
        rb = GetComponent<Rigidbody>();
    }

    void FixedUpdate()
    {
        float moveVertical = Input.GetAxis("Vertical");
        Vector3 movement = new Vector3(moveVertical * Mathf.Sin(Mathf.Deg2Rad * cameraObj.transform.rotation.eulerAngles.y), 0.0f, moveVertical * Mathf.Cos(Mathf.Deg2Rad*cameraObj.transform.rotation.eulerAngles.y));
        Debug.Log("movement: " + movement);
        rb.AddForce(movement*500);
    }

    void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.CompareTag("pickup"))
        {
            other.gameObject.SetActive(false);
            score +=  other.GetComponent<ScoreObject>().myValue;
            scoreText.text = "Score: " + score;
        }
    }
}