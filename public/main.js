$(document).ready(function () {
  $('#btnGen').click(function () {
    $('#result').empty();

    $.ajax({
      type: 'POST',
      contentType: "application/json",
      url: '/genlicense',
      dataType: 'json',
      data: JSON.stringify({
        username: $('#inputAccount').val(),
        passwd: $('#inputPassword').val(),
        due: $('#inputExpireDay').val()
      }),
      error: function (xhr) {
        console.dir(xhr.responseJSON.error);
        $('#result').text('Error: ' + xhr.responseJSON.error);
      },
      success: function(res) {
        $('#result').text('Download path: http://' + res.licenseDLPath);
      }
    });
  });
});
