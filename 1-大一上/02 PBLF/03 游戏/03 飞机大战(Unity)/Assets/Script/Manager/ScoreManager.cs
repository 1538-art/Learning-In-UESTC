using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class ScoreManager : MonoBehaviour
{
    public int score;
    public UnityEvent<int> ScoreChanged;

    private void Start()
    {
        score = 0;
        PlayerPrefs.SetInt("score", score);
    }
    public void ChangeScore(int value)
    {
        score += value;
        PlayerPrefs.SetInt("score", score);
        ScoreChanged?.Invoke(score);
    }


}
