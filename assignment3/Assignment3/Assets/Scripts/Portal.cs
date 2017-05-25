using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Portal : MonoBehaviour {

    public string levelName;

    void OnTriggerEnter(Collider other)
    {
        GameObject.Find("ScoreController").GetComponent<ScoreController>().score = Random.Range(0, 11000);
        SceneManager.LoadScene(levelName);
    }
}
